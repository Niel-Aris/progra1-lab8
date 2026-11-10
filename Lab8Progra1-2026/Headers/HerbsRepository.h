#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "DataLoader.h"

class HerbsRepository {
public:
    HerbsRepository();

    int GetAvailableQuantity(const std::string& herbType) const;
    void UpdateQuantity(const std::string& herbType, int newQuantity);

private:
    void SaveToFile() const;

    mutable std::unordered_map<std::string, std::vector<std::string>> data_;
};
