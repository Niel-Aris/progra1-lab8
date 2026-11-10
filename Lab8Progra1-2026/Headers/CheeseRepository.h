#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "DataLoader.h"

class CheeseRepository {
public:
    CheeseRepository();

    int GetAvailableQuantity(const std::string& cheeseType) const;
    void UpdateQuantity(const std::string& cheeseType, int newQuantity);

private:
    void SaveToFile() const;

    mutable std::unordered_map<std::string, std::vector<std::string>> data_;
};
