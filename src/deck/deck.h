#pragma once

#include <string>
#include <vector>

namespace SRSEngine {
struct Card;

enum ReviewQuality {
  Fail,   // user forgot the card during review
  Pass,   // user remembered normally
  Known,  // user already knows it / easy
  Reset   // reset the card to initial state
};

class Deck {
 public:
  int id;
  std::string name;
  std::vector<Card> cards;
  std::vector<Card*> dueCards;
  size_t currentIndex = 0;
  int learningPhaseLength = 3;

  // Card Management
  void AddCard(Card& card);
  void EditCard(Card& card);
  void DeleteCard(int cardId);

  // SRS Functions
  Card* GetNextCard();
  std::vector<Card*> PrepareDueCards(time_t now);
  bool IsDueToday(const Card& card, time_t todayMidnight);
  void RequeueCard(Card* card);
  bool HasCardsDue() const;
  void ReviewCard(Card& card, ReviewQuality quality, time_t todayMidnight);
  void ShuffleDeck();
};
}  // namespace SRSEngine
