#include "HerbsRepository.h"
#include <fstream>
#include <stdexcept>


HerbsRepository::HerbsRepository() {
    auto data = DataLoader::LoadFromFile("herbs.txt");
    data_ = std::move(data);
}

int HerbsRepository::GetAvailableQuantity(const std::string& herbType) const {
    auto it = data_.find(herbType);
    if (it == data_.end()) {
        throw std::invalid_argument("Tipo de hierba desconocido: " + herbType);
    }
    return std::stoi(it->second[0]);
}

void HerbsRepository::UpdateQuantity(const std::string& herbType, int newQuantity) {
    auto it = data_.find(herbType);
    if (it == data_.end()) {
        throw std::invalid_argument("Tipo de hierba desconocido: " + herbType);
    }
    it->second[0] = std::to_string(newQuantity);
    SaveToFile();
}

// guarda las cantidades en el txt para que no se pierdan al cerrar
// lee los nombres del archivo primero para que no se desordenen las lineas
void HerbsRepository::SaveToFile() const {
    std::string path = "Data/herbs.txt";
    std::ifstream in(path);
    if (!in) {
        path = "herbs.txt";
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
