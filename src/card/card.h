#pragma once

#include <string>
#include <unordered_map>

namespace SRSEngine {

enum StudyPhase { New, Young, Learning, Mature };

struct Card {
  int id;
  std::unordered_map<std::string, std::string> fields;
  int intervalDays = 0;
  double easeFactor = 2.5f;
  int repetitions = 0;
  time_t lastReview = 0;
  time_t dueDate = 0;
  int learningStep = 0;
  StudyPhase studyPhase = StudyPhase::New;
};

}  // namespace SRSEngine
