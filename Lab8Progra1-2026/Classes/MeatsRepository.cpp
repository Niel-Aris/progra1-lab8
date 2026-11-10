#include "MeatsRepository.h"
#include <fstream>
#include <stdexcept>


MeatsRepository::MeatsRepository() {
    auto data = DataLoader::LoadFromFile("meats.txt");
    data_ = std::move(data);
}

int MeatsRepository::GetAvailableQuantity(const std::string& meatType) const {
    auto it = data_.find(meatType);
    if (it == data_.end()) {
        throw std::invalid_argument("Tipo de carne desconocido: " + meatType);
    }
    return std::stoi(it->second[0]);
}

void MeatsRepository::UpdateQuantity(const std::string& meatType, int newQuantity) {
    auto it = data_.find(meatType);
    if (it == data_.end()) {
        throw std::invalid_argument("Tipo de carne desconocido: " + meatType);
    }
    it->second[0] = std::to_string(newQuantity);
    SaveToFile();
}

// guarda las cantidades en el txt para que no se pierdan al cerrar
// lee los nombres del archivo primero para que no se desordenen las lineas
void MeatsRepository::SaveToFile() const {
    std::string path = "Data/meats.txt";
    std::ifstream in(path);
    if (!in) {
        path = "meats.txt";
        in.clear();
        in.open(path);
    }
    if (!in) {
        throw std::runtime_error("No se puede abrir el archivo: " + path);
    }

    std::vector<std::string> nombres;
    std::string line;
    while (std::getline(in, line)) {
        auto pos = line.find(':');
        if (pos != std::string::npos) {
            nombres.push_back(line.substr(0, pos));
        }
    }
    in.close();

    std::ofstream out(path);
    if (!out) {
        throw std::runtime_error("No se puede guardar el archivo: " + path);
    }
    for (const auto& nombre : nombres) {
        auto it = data_.find(nombre);
        if (it != data_.end()) {
            out << nombre << ": " << it->second[0] << "\n";
        }
    }
}
