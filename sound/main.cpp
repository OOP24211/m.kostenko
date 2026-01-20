#include "processor/Processor.hpp"
#include "converters/ConverterFactory.hpp"
#include "exceptions/Exceptions.hpp"

#include <iostream>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
    try {
        
        if (argc == 2 && std::string(argv[1]) == "-h") {
            ConverterFactory::printHelp();
            return 0;
        }

        if (argc < 5) {
            throw ArgError(
                "Usage: sound_processor -c <config.txt> <output.wav> <input1.wav> [input2.wav ...]\n"
                "       sound_processor -h"
            );
        }

        std::string flag = argv[1];
        if (flag != "-c") {
            throw ArgError("Expected -c as first argument");
        }

        std::string configPath = argv[2];
        std::string outputPath = argv[3];

        std::vector<std::string> inputPaths;
        for (int i = 4; i < argc; ++i) {
            inputPaths.push_back(argv[i]);
        }

        if (inputPaths.empty()) {
            throw ArgError("At least one input file is required");
        }

        // Create and run the processor
        Processor processor(configPath, outputPath, inputPaths);
        processor.run();

        std::cout << "Processing completed successfully.\n";
        return 0;
    }

    catch (const ArgError& e) {
        std::cerr << "Argument error: " << e.what() << "\n";
        return 1;
    }
    catch (const WavFormatError& e) {
        std::cerr << "WAV format error: " << e.what() << "\n";
        return 2;
    }
    catch (const ConfigError& e) {
        std::cerr << "Config error: " << e.what() << "\n";
        return 3;
    }
    catch (const RuntimeError& e) {
        std::cerr << "Runtime error: " << e.what() << "\n";
        return 4;
    }
    catch (const std::exception& e) {
        std::cerr << "Unknown error: " << e.what() << "\n";
        return 5;
    }
}
