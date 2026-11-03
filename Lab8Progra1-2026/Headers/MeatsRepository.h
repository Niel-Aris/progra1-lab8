#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "DataLoader.h"

class MeatsRepository {
public:
    MeatsRepository();

    int GetAvailableQuantity(const std::string& meatType) const;
    void UpdateQuantity(const std::string& meatType, int newQuantity);

private:
    void SaveToFile() const;

    mutable std::unordered_map<std::string, std::vector<std::string>> data_;
};
