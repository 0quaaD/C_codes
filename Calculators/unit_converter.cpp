#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <vector>

struct Messages {
    static void showOptions() {
        std::cout << "\nEnter the conversion type:\n";
        std::cout << "'lim' -> imperial length to metric length\n";
        std::cout << "'lmi' -> metric length to imperial length\n";
        std::cout << "'lii' -> imperial to imperial length\n";
        std::cout << "'lmm' -> metric to metric length\n\n";
        
		std::cout << "'wim' -> imperial length to metric weight\n";
        std::cout << "'wmi' -> metric length to imperial weight\n";
        std::cout << "'wii' -> imperial to imperial weight\n";
        std::cout << "'wmm' -> metric to metric weight\n\n";
		
		std::cout << "'tim' -> imperial temperature (F) to metric temperature (C)\n";
        std::cout << "'tmi' -> metric temperature (C) to imperial temperature (F)\n";
        std::cout << "'tik' -> imperial  temperature (F) to kelvin temperature (K)\n";
        std::cout << "'tmk' -> metric temperature (C) to metric temperature\n";
		std::cout << "'tki' -> kelvin temperature (K) to imperial temperature (F)\n";
		std::cout << "'tkm' -> kelvin temperature (K) to metric temperature (C)\n\n";
        
		std::cout << "Choice: ";
    }

    static void showImperialLenUnits() {
        std::cout << "\nAvailable units: 'in' (inches), 'ft' (feet), 'yd' (yards), 'mi' (miles)\n";
        std::cout << "Input (e.g. '5 in' or '12 yd'): ";
    }

    static void showMetricLenUnits() {
        std::cout << "\nAvailable units: 'mm' (millimeters), 'cm' (centimeters), 'm' (meters), 'km' (kilometers)\n";
        std::cout << "Input (e.g. '5 cm' or '12 km'): ";
    }

	static void showImperialWeightUnits(){
		std::cout << "\nAvailable units: 'oz' (ounces), 'lb' (pound)\n";
		std::cout << "Input (e.g. '5 oz' or '29 lb'): ";
	}

	static void showMetricWeightUnits(){
		std::cout << "\nAvailable units: 'mg' (milligram), 'g' (gram), 'kg' (kilogram), 't' (tonnes)\n";
		std::cout << "Input (e.g. '5 kg' or '29 t'): ";
	}

	static void showImperialTempUnits(){
		std::cout << "\nAvailable unit: 'F'\n";
		std::cout << "Input (e.g. '42.1 F' or '32 F'): ";
	}
	
	static void showMetricTempUnits(){
		std::cout << "\nAvailable unit: 'C'\n";
		std::cout << "Input (e.g. '42.1 C' or '32 C'): ";
	}
	
	static void showKelvinTempUnits(){
		std::cout << "\nAvailable unit: 'K'\n";
		std::cout << "Input (e.g. '421 K' or '322 K'): ";
	}
};

class UnitConverter {
private:
    // Conversion factors to meters (base unit)
    static const std::unordered_map<std::string, double> imperialToMeters;
    static const std::unordered_map<std::string, double> metricToMeters;

	static const std::unordered_map<std::string, double> imperialToGrams;
    static const std::unordered_map<std::string, double> metricToGrams;

    struct ConversionResult {
        double value;
        std::string unit;
        int precision;
    };

public:
    static bool parseInput(const std::string& input, double& value, std::string& unit) {
        std::istringstream iss(input);
        return static_cast<bool>(iss >> value >> unit);
    }

    static bool isValidImperialUnit(const std::string& unit) {
        return imperialToMeters.find(unit) != imperialToMeters.end();
    }

    static bool isValidMetricUnit(const std::string& unit) {
        return metricToMeters.find(unit) != metricToMeters.end();
    }

	static bool isValidImperialWeightUnit(const std::string& unit){
		return imperialToGrams.find(unit) != imperialToGrams.end();
	}

	static bool isValidMetricWeightUnit(const std::string& unit){
		return metricToGrams.find(unit) != metricToGrams.end();
	}


    // Imperial to Metric conversion
    static void convertImperialToMetric(double value, const std::string& unit) {
        if (!isValidImperialUnit(unit)) {
            throw std::invalid_argument("Invalid imperial unit: " + unit);
        }

        double meters = value * imperialToMeters.at(unit);
        double centimeters = meters * 100;

        std::cout << "Result: " << std::fixed;
        
        if (unit == "mi") {
            std::cout << std::setprecision(1) << centimeters << " cm or " 
                     << std::setprecision(3) << meters << " m\n";
        } else {
            std::cout << std::setprecision(1) << centimeters << " cm or " 
                     << std::setprecision(3) << meters << " m\n";
        }
    }

    // Metric to Imperial conversion
    static void convertMetricToImperial(double value, const std::string& unit) {
        if (!isValidMetricUnit(unit)) {
            throw std::invalid_argument("Invalid metric unit: " + unit);
        }

        double meters = value * metricToMeters.at(unit);
        double inches = meters / imperialToMeters.at("in");
        double yards = meters / imperialToMeters.at("yd");
        double miles = meters / imperialToMeters.at("mi");

        std::cout << "Result: " << std::fixed << std::setprecision(6);
        
        if (unit == "km") {
            std::cout << yards << " yards (yd) or " << miles << " miles (mi)\n";
        } else {
            std::cout << inches << " inches (in) or " << yards << " yards (yd)\n";
        }
    }

    // Imperial to Imperial conversion
    static void convertImperialToImperial(double value, const std::string& unit) {
        if (!isValidImperialUnit(unit)) {
            throw std::invalid_argument("Invalid imperial unit: " + unit);
        }

        double meters = value * imperialToMeters.at(unit);
        
        std::cout << "Result:\n" << std::fixed;
        
        for (const auto& [targetUnit, factor] : imperialToMeters) {
            if (targetUnit != unit) {
                double converted = meters / factor;
                int precision = (targetUnit == "mi") ? 9 : 6;
                std::cout << std::setprecision(precision) << converted << " " << targetUnit << "\n";
            }
        }
    }

    // Metric to Metric conversion
    static void convertMetricToMetric(double value, const std::string& unit) {
        if (!isValidMetricUnit(unit)) {
            throw std::invalid_argument("Invalid metric unit: " + unit);
        }

        double meters = value * metricToMeters.at(unit);
        
        std::cout << "Result:\n" << std::fixed;
        
        // Order: mm, cm, m, km
        std::vector<std::string> orderedUnits = {"mm", "cm", "m", "km"};
        
        for (const std::string& targetUnit : orderedUnits) {
            if (targetUnit != unit) {
                double converted = meters / metricToMeters.at(targetUnit);
                int precision = (targetUnit == "km" && unit != "km") ? 6 : 3;
                std::cout << std::setprecision(precision) << converted << " " << targetUnit << "\n";
            }
        }
    }

	static void convertImperialWeightToMetric(double value, const std::string& unit){
		if(!isValidImperialWeightUnit(unit)){
			throw std::invalid_argument("Invalid imperial weight unit: " + unit);
		}
		double grams = value * imperialToGrams.at(unit);
		double kilograms = grams / 1000.0f;
		std::cout << "Result:\n" << std::fixed;
		
		if(unit == "lb"){
			std::cout << std::setprecision(1) << grams << " g or " << std::setprecision(3) << kilograms << " kg\n";
		}
		else{
			std::cout << std::setprecision(1) << grams << " g or " << std::setprecision(3) << kilograms << " kg\n";
		}
	}

	static void convertMetricWeightToImperial(double value, const std::string& unit){
		if(!isValidMetricWeightUnit(unit)){
			throw std::invalid_argument("Invalid metric weight unit: " + unit);
		}
		double grams = value * metricToGrams.at(unit);
		double ounces = grams / imperialToGrams.at("oz");
		double pounds = grams / imperialToGrams.at("lb");
		std::cout << "Result:\n" << std::fixed << std::setprecision(6);
		
		if(unit == "t" || unit == "kg"){
			std::cout << pounds << " lb or " << ounces << " oz\n";
		}
		else{
			std::cout << ounces << " oz or " << pounds << " lb\n";
		}
	}

	static void convertMetricWeightToMetric(double value, const std::string& unit){
		if(!isValidMetricWeightUnit(unit))
			throw std::invalid_argument("Invalid metric weight argument: " + unit);

		double grams = value * metricToGrams.at(unit);
		std::vector<std::string> orderedMetricWeights = {"mg", "g", "kg", "t"};
		std::cout << "Result:\n" << std::fixed;
		for(const std::string& targetUnit : orderedMetricWeights){
			if(targetUnit != unit){
				double converted = grams / metricToGrams.at(targetUnit);
				int precision = (targetUnit == "t" && unit != "t") ? 9 : 6;
				std::cout << std::setprecision(precision) << converted << " " << targetUnit << "\n";
			}
		}
	}

	static void convertImperialWeightToImperial(double value, const std::string& unit){
		if(!isValidImperialWeightUnit(unit))
			throw std::invalid_argument("Invalid imperial weight unit: " + unit);
		
		double grams = value * imperialToGrams.at(unit);
		std::cout << "Result:\n";
		for(const auto& [targetUnit, factor] : imperialToGrams){
			if(targetUnit != unit){
				double converted = grams / imperialToGrams.at(targetUnit);
				int precision = (targetUnit == "lb") ? 6 : 3;
				std::cout << std::setprecision(precision) << converted << " " << targetUnit << "\n";
			}
		}
	}
	
	static void convertImperialTempToMetric(double value, const std::string& unit){
		if(unit != "F")
			throw std::invalid_argument("Invalid imperial temperature unit: " + unit);

		std::cout << "Result:\n" << std::fixed;
		double cels = (value - 32) / 1.8f;
		std::cout << std::setprecision(1) << cels << " C\n";
	}
	
	static void convertImperialTempToKelvin(double value, const std::string& unit){
		if(unit != "F")
			throw std::invalid_argument("Invalid imperial temperature unit: " + unit);

		std::cout << "Result:\n" << std::fixed;
		double kelvin = ((value - 32) / 1.8f) + 273.15f;
		std::cout << std::setprecision(1) << kelvin << " K\n";
	}
	
	static void convertMetricTempToImperial(double value, const std::string& unit){
		if(unit != "C")
			throw std::invalid_argument("Invalid metric temperature unit: " + unit);

		std::cout << "Result:\n" << std::fixed;
		double fah = (value * 1.8f) + 32.0f; 
		std::cout << std::setprecision(1) << fah << " F\n";
	}
	
	static void convertMetricTempToKelvin(double value, const std::string& unit){
		if(unit != "C")
			throw std::invalid_argument("Invalid metric temperature unit: " + unit);

		std::cout << "Result:\n" << std::fixed;
		double kelvin = value + 273.15f;
		std::cout << std::setprecision(1) << kelvin << " K\n";
	}
	
	static void convertKelvinTempToImperial(double value, const std::string& unit){
		if(unit != "K")
			throw std::invalid_argument("Invalid kelvin temperature unit: " + unit);

		std::cout << "Result:\n" << std::fixed;
		double fah = ((value - 273.15f) * 1.8f) + 32;
		std::cout << std::setprecision(1) << fah << " F\n";
	}
	
	static void convertKelvinTempToMetric(double value, const std::string& unit){
		if(unit != "K")
			throw std::invalid_argument("Invalid kelvin temperature unit: " + unit);

		std::cout << "Result:\n" << std::fixed;
		double cels = value - 273.15f;
		std::cout << std::setprecision(1) << cels << " C\n";
	}

};

// Initialize static conversion factors
const std::unordered_map<std::string, double> UnitConverter::imperialToMeters = {
    {"in", 0.0254},
    {"ft", 0.3048},
    {"yd", 0.9144},
    {"mi", 1609.344}
};

const std::unordered_map<std::string, double> UnitConverter::metricToMeters = {
    {"mm", 0.001},
    {"cm", 0.01},
    {"m", 1.0},
    {"km", 1000.0}
};

const std::unordered_map<std::string, double> UnitConverter::metricToGrams = {
	{"mg", 0.001},
	{"g", 1.0},
	{"kg", 1000.0},
	{"t", 1000000.0}
};

const std::unordered_map<std::string, double> UnitConverter::imperialToGrams = {
	{"oz", 	28.34952},
	{"lb", 453.5924}
};

class ConversionHandler {
public:
    static void handleConversion(const std::string& choice) {
        std::string input, unit;
        double value;

        try {
            if (choice == "lim") {
                Messages::showImperialLenUnits();
                std::getline(std::cin, input);
                
                if (UnitConverter::parseInput(input, value, unit)) {
                    UnitConverter::convertImperialToMetric(value, unit);
                } else {
                    std::cout << "Invalid input format! Use format like '12 in' or '5 yd'\n";
                }
            }
            else if (choice == "lmi") {
                Messages::showMetricLenUnits();
                std::getline(std::cin, input);
                
                if (UnitConverter::parseInput(input, value, unit)) {
                    UnitConverter::convertMetricToImperial(value, unit);
                } else {
                    std::cout << "Invalid input format! Use format like '5 cm' or '1 km'\n";
                }
            }
            else if (choice == "lii") {
                Messages::showImperialLenUnits();
                std::getline(std::cin, input);
                
                if (UnitConverter::parseInput(input, value, unit)) {
                    UnitConverter::convertImperialToImperial(value, unit);
                } else {
                    std::cout << "Invalid input format!\n";
                }
            }
            else if (choice == "lmm") {
                Messages::showMetricLenUnits();
                std::getline(std::cin, input);
                
                if (UnitConverter::parseInput(input, value, unit)) {
                    UnitConverter::convertMetricToMetric(value, unit);
                } else {
                    std::cout << "Invalid input format!\n";
                }
            }
	    else if(choice == "wim"){
		    Messages::showImperialWeightUnits();
		    std::getline(std::cin, input);
		    if(UnitConverter::parseInput(input, value, unit)){
			    UnitConverter::convertImperialWeightToMetric(value, unit);
		    }
		    else{
			    std::cout << "Invalid imperial input format!\n";
		    }
	    }
	    else if(choice == "wmi"){
		    Messages::showMetricWeightUnits();
		    std::getline(std::cin, input);
		    if(UnitConverter::parseInput(input, value, unit)){
			    UnitConverter::convertMetricWeightToImperial(value, unit);
		    }
		    else{
			    std::cout << "Invalid metric input format!\n";
		    }
	    }
	    else if(choice == "wii"){
		    Messages::showImperialWeightUnits();
		    std::getline(std::cin, input);
		    if(UnitConverter::parseInput(input, value, unit)){
			    UnitConverter::convertImperialWeightToImperial(value, unit);
		    }
		    else {
			    std::cout << "Invalid imperial input format!\n";
		    }
	    }
	    else if(choice == "wmm"){
		    Messages::showMetricWeightUnits();
		    std::getline(std::cin, input);
		    if(UnitConverter::parseInput(input, value, unit)){
			    UnitConverter::convertMetricWeightToMetric(value, unit);
		    }
		    else{
			    std::cout << "Invalid metric input format!\n";
		    }
	    }
	    else if(choice == "tim"){
	    	    Messages::showImperialTempUnits();
		    std::getline(std::cin, input);
		    if(UnitConverter::parseInput(input, value, unit))
			    UnitConverter::convertImperialTempToMetric(value, unit);
		    else
			    std::cout << "Invalid imperial temperature input format!\n";
	    }
	    else if(choice == "tmi"){
		    Messages::showMetricTempUnits();
		    std::getline(std::cin, input);
		    if(UnitConverter::parseInput(input, value, unit))
			    UnitConverter::convertMetricTempToImperial(value, unit);
		    else
			    std::cout << "Invalid metric temperature input format!\n";
	    }
	
	    else if(choice == "tik"){
	  	    Messages::showImperialTempUnits();
		    std::getline(std::cin, input);
		    if(UnitConverter::parseInput(input, value, unit))
			    UnitConverter::convertImperialTempToKelvin(value, unit);
		    else
			    std::cout << "Invalid imperial temperature input format!\n";
	    }
	    else if(choice == "tmk"){
		    Messages::showMetricTempUnits();
		    std::getline(std::cin, input);
		    if(UnitConverter::parseInput(input, value, unit))
			    UnitConverter::convertMetricTempToKelvin(value, unit);
		    else
			    std::cout << "Invalid metric temperature input format!\n";
	    }
	    else if(choice == "tki"){
		    Messages::showKelvinTempUnits();
		    std::getline(std::cin, input);
		    if(UnitConverter::parseInput(input, value, unit))
			    UnitConverter::convertKelvinTempToImperial(value, unit);
		    else
			    std::cout << "Invalid kelvin temperature input format!\n";
	    }
	
	    else if(choice == "tkm"){
		    Messages::showKelvinTempUnits();
		    std::getline(std::cin, input);
		    if(UnitConverter::parseInput(input, value, unit))
			    UnitConverter::convertKelvinTempToMetric(value, unit);
		    else
			    std::cout << "Invalid kelvin temperature input format!\n";
	    }
            else {
                    std::cout << "Invalid choice!\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
};

int main() {
    std::string choice;
    Messages::showOptions();
    std::getline(std::cin, choice);
    
    ConversionHandler::handleConversion(choice);
    
    return 0;
}
