//Assignment 2_ Team 17                                     
//Comp 345_fall 2017   


#include "MapLoader.h"

MapLoader::MapLoader(std::string fileName, Map& map){
	std::ifstream inputfile;
	inputfile.open(fileName);

	std::string line;
	std::vector<std::string> tokenizer;
	std::vector<std::string> continents;
	std::vector<std::string> conts;
	vector<std::string> country;
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
		int d = std::stoi(line.substr(b + 1));
		conts.push_back( line.substr(0, b));
		map.addContinent(line.substr(0, b));
		map.setValueContinent(line.substr(0, b),std::stoi(line.substr(b+1)));
		//std::cout << "value of continent" << d << endl;
		//std::cout << "Continent: " << line.substr(0, b) << std::endl;
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
		
		map.addNode(token);
		//std::cout << "Adding country: " << token << std::endl;
	}
	// Create contries of each continent from every line
	/*for (int i = continents.size() - 1; i >= 0; i--) {
		int b = continents[i].find(search);
		while (!line.empty()){
			country.push_back(continents[i].substr(0, b));
		} ;
		for (int j = conts.size() - 1; j >= 0; j--) {
			for (int z = 0; z < country.size(); z++) {
				map.addContinentCountry(conts[j], country[z]);
			}
		}
	}
	*/
	

	

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

		map.addContinentCountry(tokenizer[3], tokenizer[0]);

		for (int i = tokenizer.size() - 1; i > 3; i--){
			
			map.addCountryNeighbor(tokenizer[0], tokenizer[i]);
			//std::cout << "Creating Edge for: " << tokenizer[0] << " and " << tokenizer[i] << std::endl;
		}

		tokenizer.clear();
	}
}