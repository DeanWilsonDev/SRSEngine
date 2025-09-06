#include "deck/deck.h"
#include "card/card.h"
#include <ios>
#include <iostream>
#include <limits>

SRSEngine::ReviewQuality ParseInput(const std::string& input)
{
  if (input == "1") return SRSEngine::ReviewQuality::Fail;
  if (input == "2") return SRSEngine::ReviewQuality::Pass;
  if (input == "k") return SRSEngine::ReviewQuality::Known;
  if (input == "r") return SRSEngine::ReviewQuality::Reset;
  return SRSEngine::ReviewQuality::Fail;
}

bool IsTriggerExit(const std::string& input)
{
  if (input == "e") {
    std::cout << "\nLeaving study session...\n";
    return true;
  }
  return false;
}

int main()
{
  SRSEngine::Deck deck;

  SRSEngine::Card c1{0, {{"front", "Hund"}, {"back", "Dog"}}};
  SRSEngine::Card c2{1, {{"front", "Katze"}, {"back", "Cat"}}};
  SRSEngine::Card c3{2, {{"front", "Haus"}, {"back", "House"}}};

  deck.AddCard(c1);
  deck.AddCard(c2);
  deck.AddCard(c3);

  time_t now = time(nullptr);
  tm* local_tm = localtime(&now);

  local_tm->tm_hour = 0;
  local_tm->tm_min = 0;
  local_tm->tm_sec = 0;

  time_t today_midnight = mktime(local_tm);

  deck.PrepareDueCards(today_midnight);

  SRSEngine::Card* card;
  while ((card = deck.GetNextCard()) != nullptr) {
    std::cout << "\nFront: " << card->fields["front"] << std::endl;
    std::cout << "Press Enter to reveal the back...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    std::cout << "Back: " << card->fields["back"] << std::endl;
    std::cout << "Enter 1=Fail 2=Pass k=Known r=Reset e=Exit: ";

    std::string input;
    std::cin >> input;
    SRSEngine::ReviewQuality quality = ParseInput(input);

    if (IsTriggerExit(input)) return 0;

    deck.ReviewCard(*card, quality, today_midnight);
    std::cout << "Card reviewed. Next due in " << card->intervalDays << " days(s).\n";
  }

  std::cout << "\nAll cards for today reviewed!\n";
  return 0;
}
