/* Assignment 1-Part2(MapLoader)-Fall 2017
Comp345- Team 17

*/

#include "stdafx.h"
#include "MapLoader.h"

MapLoader::MapLoader(std::string fileName){
	std::ifstream inputfile;
	inputfile.open(fileName);

	std::string line;
	std::vector<std::string> tokenizer;
	std::vector<std::string> continents;
	std::string search = ",";
	int pos;

	// Verify if map file is valid
	std::getline(inputfile, line);
	if (line != "[Map]"){
		std::cerr << "Error: Invalide Map File" << std::endl;
		exit(-1);
	}

	do{
		std::getline(inputfile, line);
		//Verify if map file is valid
		if (inputfile.eof()){
			std::cerr << "Error: Invalide Map File" << std::endl;
			exit(-1);
		}
	} while (line != "[Continents]");

	//Create continent nodes from [Continent]
	do{
		std::getline(inputfile, line);
		
		if (line.empty()){
			break;
		}
		int b = line.find("=");
		std::cout << "Continent: " << line.substr(0, b) << std::endl;
	} while (true);

	do{
		std::getline(inputfile, line);
		// Verify if map file is valid
		if (inputfile.eof()){
			std::cerr << "Error: Invalide Map File" << std::endl;
			exit(-1);
		}
	} while (line != "[Territories]");

	// Create vector for every line of [Territories]
	do{

		if (inputfile.eof()){
			break;
		}

		std::getline(inputfile, line);

		if (line.empty()){
		}
		else{
			continents.push_back(line);
		}
	} while (true);

	inputfile.close();

	// Create a country from every line
	for (int i = continents.size()-1; i >= 0; i--){
		std::string token;
		int b = continents[i].find(search);
		token = continents[i].substr(0, b);
		
		std::cout << "Adding country: " << token << std::endl;
	}

	// Create adjacencies to countries
	for (int i = continents.size() - 1; i >= 0; i--){
		std::string  temp;
		//tokenize one string from continents vector
		while (continents[i].find(",", 0) != std::string::npos){
			size_t  pos = continents[i].find(",", 0); //store the position of the delimiter
			temp = continents[i].substr(0, pos);      //get the token
			continents[i].erase(0, pos + 1);          //erase it from the source 
			tokenizer.push_back(temp);                //and put it into the array
		}
		tokenizer.push_back(continents[i]);           //the last token is all alone 

		for (int i = tokenizer.size() - 1; i > 3; i--){
			
			std::cout << "Creating Edge for: " << tokenizer[0] << " and " << tokenizer[i] << std::endl;
		}

		tokenizer.clear();
	}
}