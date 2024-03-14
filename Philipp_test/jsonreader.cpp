Changed jsonreader.cpp by PhiProjekt

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
    #include <config.h>
#include <pathtest.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include <jsoncpp/json/json.h>

#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

#include <boost/format.hpp>

//Das sind die Logging spezifischen Includes
//Erster Teil wird nur zum initalisieren benötigt
#include <filesink.h>
#include <consolesink.h>

//In jeder Datei in der Logging statt findet müssen diese zwei Zeilen includiert werden
#include <logging.h>
LOGGING_INSTANCE();

/**
 * @brief Die Einstiegsfunktion in das Programm
 * 
 * @param argc Anzahl der Argumente
 * @param argv Argumente als String
 * @return <c>0</c> bei Erfolg, sonst <c>!0</c>
 */
int main(const int argc, const char **argv) {

    auto textlogsink = boost::make_shared<CFileSink>("Textlog", str(boost::format("%s.log") % MAIN_PROJECTNAME));
    auto consolelogsink = boost::make_shared<CConsoleSink>("Consolelog");

    {
        //Registrierung im Logging System
        CLoggingHelper::connect(textlogsink, [&textlogsink]()->bool {
            boost::shared_ptr<logging::core> core = CLoggingHelper::getCore();

            core->add_sink(textlogsink);
            return true;
        });

        CLoggingHelper::connect(consolelogsink, [&consolelogsink]()->bool {
            boost::shared_ptr<logging::core> core = CLoggingHelper::getCore();

            core->add_sink(consolelogsink);
            return true;
        });
    }

    //Hier kann der Log Level eingestellt werden
    textlogsink->setCurrentLoggerLevel(ELoggerLevel::DEBUG);

    auto success = [&textlogsink, &consolelogsink]()-> bool {
        LOG(ELoggerLevel::INFO) << "Programm erfolgreich beendet";
        CLoggingHelper::disconnect();
        return EXIT_SUCCESS;
    };

    auto failure = [&textlogsink, &consolelogsink]()-> bool {
        LOG(ELoggerLevel::INFO) << "Programm mit Fehler beendet";
        CLoggingHelper::disconnect();
        return EXIT_FAILURE;
    };

    LOG(ELoggerLevel::INFO) << "Programm Start";

    //Simples Beispiel zum auslesen einer json Datei
    if(argc != 2) {
        LOG(ELoggerLevel::CONSOLEERROR) << "Bitte eine Datei angeben!";
        return failure();
    }
    else {
        auto path = fs::weakly_canonical(argv[1]);

        if(!fs::exists(path)) {
            LOG(ELoggerLevel::CONSOLEERROR) << "Datei existiert nicht: " << formatValueForLogging(path.string());
            return failure();
        }

        ifstream ifs(path.string());

        Json::Reader reader;
        Json::Value root;
        if(!reader.parse(ifs, root)) {
            LOG(ELoggerLevel::CONSOLEERROR) << "Datei ist ungueltig: " << formatValueForLogging(path.string());
            return failure();
        }

        //Zuerst wird das Land ausgeben
        cout << "Land: " << root["country"].asString() << endl;

        {
            //Werte aus dem Array
            const Json::Value persons = root["persons"];

            if(persons.isArray())
                for (Json::Value::ArrayIndex i = 0; i < persons.size(); ++i) {
                    auto person = persons[i];

                    cout << "Id: " << person["id"].asInt() << endl;
                    //..... usw .....
                }
        }

        return success();
    }
}
