#include "deck.h"

#include <vector>
#include <algorithm>
#include <random>
#include "card/card.h"

namespace SRSEngine {

void Deck::AddCard(Card& card)
{
  this->cards.push_back(card);
}

void Deck::EditCard(Card& card)
{
  for (Card c : this->cards) {
    if (c.id == card.id) {
      c = card;
    }
  }
}

void Deck::DeleteCard(int id)
{
  for (size_t i = 0; i < this->cards.size(); ++i) {
    if (this->cards[i].id == id) {
      this->cards[i] = this->cards.back();
      this->cards.pop_back();
      break;
    }
  }
}

Card* Deck::GetNextCard()
{
  if (currentIndex < this->dueCards.size()) {
    return this->dueCards[currentIndex++];
  }
  return nullptr;
}

bool Deck::IsDueToday(const Card& card, time_t todayMidnight)
{
  return card.dueDate <= todayMidnight;
}

std::vector<Card*> Deck::PrepareDueCards(time_t todayMidnight)
{
  this->dueCards.clear();
  for (auto& card : this->cards) {
    if (card.dueDate <= todayMidnight) {
      this->dueCards.push_back(&card);
    }
  }

  ShuffleDeck();
  return this->dueCards;
}

void Deck::RequeueCard(Card* card)
{
  this->dueCards.push_back(card);
}

bool Deck::HasCardsDue() const
{
  return !this->dueCards.empty();
}

void Deck::ReviewCard(Card& card, ReviewQuality quality, time_t todayMidnight)
{
  switch (quality) {
    case ReviewQuality::Fail:
      card.repetitions = 0;
      card.learningStep = 0;
      card.intervalDays = 0;
      card.easeFactor = std::max(1.3, card.easeFactor - 0.2f);
      break;
    case ReviewQuality::Pass:
      switch (card.studyPhase) {
        case StudyPhase::New:
          if (card.repetitions == 0) {
            card.learningStep++;
            bool isStillLearning = card.learningStep < this->learningPhaseLength;
            if (isStillLearning) {
              card.dueDate = todayMidnight;  // This might want to get set to now
              RequeueCard(&card);
              return;
            }
            else {
              card.repetitions = 1;
              card.intervalDays = 1;
              card.studyPhase = StudyPhase::Young;
            }
          }
          break;
        case StudyPhase::Young:
          card.repetitions++;
          card.intervalDays = 1;
          card.studyPhase = StudyPhase::Learning;
          break;
        case StudyPhase::Learning:
          card.intervalDays = 6;
          card.studyPhase = StudyPhase::Mature;
          break;
        case StudyPhase::Mature:
          card.intervalDays = static_cast<int>(std::round(card.intervalDays * card.easeFactor));
          break;
      }
      break;
    case ReviewQuality::Known:
      card.repetitions++;
      card.intervalDays = static_cast<int>(std::round(card.intervalDays * card.easeFactor * 1.5f));
      card.easeFactor = 0.05;
      break;
    case ReviewQuality::Reset:
      card.repetitions = 0;
      card.intervalDays = 0;
      card.easeFactor = 2.5f;
      break;
  }

  card.lastReview = todayMidnight;
  card.dueDate = todayMidnight + card.intervalDays * 24 * 60 * 60;
}

void Deck::ShuffleDeck()
{
  std::shuffle(this->dueCards.begin(), this->dueCards.end(), std::mt19937{std::random_device{}()});
}

}  // namespace SRSEngine
