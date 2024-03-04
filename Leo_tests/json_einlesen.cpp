#include <iostream>
#include <fstream>
#include <string>
#include <vector> // Hinzugefügt für std::vector

// Definition der json-Struktur
struct JSON {
    std::string key;
    std::string value;
    // Optional: Weitere Felder hinzufügen, falls erforderlich
};

int main() {
    // Benutzereingabe für den Dateipfad
    std::cout << "Bitte gib den Dateipfad zur Datei an:\t";
    std::string filePath;
    std::cin >> filePath;

    // JSON-Datei einlesen
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Fehler beim Öffnen der Datei." << std::endl;
        return 1;
    }

    // Vektor zum Speichern der JSON-Daten
    std::vector<JSON> jsonData;

    // Zeile für Zeile einlesen und parsen
    std::string line;
    while (std::getline(file, line)) {
        // Hier implementieren Sie Ihre Logik zum Parsen der JSON-Datei
        // Die Logik hängt von der genauen Struktur Ihrer JSON-Datei ab
        // Sie können z. B. reguläre Ausdrücke oder andere Methoden verwenden
        // um die Daten zu extrahieren und in die jsonData-Struktur einzufügen
    }

    // Jetzt sind die JSON-Daten in der Variable "jsonData" gespeichert
    // Sie können die Daten weiterverarbeiten, wie Sie möchten

    return 0;
}