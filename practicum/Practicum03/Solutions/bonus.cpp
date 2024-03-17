#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
#include <sstream>
#include <limits>


const std::size_t MAX_FILENAME_LENGTH = 50;
const std::size_t MAX_NAME_LENGTH = 50;
const std::size_t MAX_TYPE_LENGTH = 20;
const std::size_t MAX_COMMAND_LENGTH = 32;
const std::size_t MAX_COMMAND_LINE_LENGTH = 256;

typedef std::uint8_t TypeUnderlyingType;

enum class Type : TypeUnderlyingType {
    NORMAL,
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    GHOST,
    FLYING,
	size,
	UNKNOWN,
};

constexpr TypeUnderlyingType TypeToUnderlyingType(Type t) {
	return static_cast<TypeUnderlyingType>(t);
}

constexpr Type TypeUnderlyingToType(TypeUnderlyingType t) {
	return static_cast<Type>(t);
}

const char* typeToString[TypeToUnderlyingType(Type::size)];

void initTypes() {
	typeToString[TypeToUnderlyingType(Type::NORMAL)] = "normal";
	typeToString[TypeToUnderlyingType(Type::FIRE)] = "fire";
	typeToString[TypeToUnderlyingType(Type::WATER)] = "water";
	typeToString[TypeToUnderlyingType(Type::GRASS)] = "grass";
	typeToString[TypeToUnderlyingType(Type::ELECTRIC)] = "electric";
	typeToString[TypeToUnderlyingType(Type::GHOST)] = "ghost";
	typeToString[TypeToUnderlyingType(Type::FLYING)] = "flying";
	typeToString[TypeToUnderlyingType(Type::UNKNOWN)] = "unknown";
}

Type stringToType(char type[]) {
	for (Type t = TypeUnderlyingToType(0); t != Type::size; t = TypeUnderlyingToType(TypeToUnderlyingType(t) + 1)) {
		if (strcmp(type, typeToString[TypeToUnderlyingType(t)]) == 0) {
			return t;
		}
	}

	return Type::UNKNOWN;
}

struct Pokemon {
    char name[MAX_NAME_LENGTH + 1];
    Type type;
    std::uint16_t power;
};

Pokemon createPokemonFromConsole() {
    Pokemon pokemon;

	char type[MAX_TYPE_LENGTH + 1];

    std::cout << "Enter Pokemon Name(max " << MAX_NAME_LENGTH << " length): ";
	std::cin.getline(pokemon.name, MAX_NAME_LENGTH);

    std::cout << "Enter Pokemon Type(max " << MAX_TYPE_LENGTH << " length): ";
	std::cin.getline(type, MAX_TYPE_LENGTH);
	pokemon.type = stringToType(type);

    std::cout << "Enter Pokemen Strength(between 10 and 1000): ";
    std::cin >> pokemon.power;
	if (pokemon.power < 10) {
		pokemon.power = 10;
	} else if (pokemon.power > 1000) {
		pokemon.power = 1000;
	}

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    return pokemon;
}

Pokemon readPokemonFromBinaryFile(std::ifstream &in) {
	Pokemon pokemon;

	in.read((char*)&pokemon, sizeof(pokemon));

	return pokemon;
}

std::ifstream& readPokemonFromFile(std::ifstream &in, Pokemon &pokemon) {
	char type[MAX_TYPE_LENGTH + 1];

    in >> pokemon.name;
	in >> type;
	pokemon.type = stringToType(type);
    in >> pokemon.power;
	if (pokemon.power < 10) {
		pokemon.power = 10;
	} else if (pokemon.power > 1000) {
		pokemon.power = 1000;
	}

    return in;
}

void writePokemonToBinaryFile(std::fstream &out, const Pokemon &pokemon) {
	out.write((const char*)&pokemon, sizeof(pokemon));
}

void writePokemonToStream(std::ostream &out, const Pokemon &pokemon) {
	out << pokemon.name << ' ' << typeToString[TypeToUnderlyingType(pokemon.type)] << ' ' << pokemon.power << '\n';
}

struct PokemonHandler {
    char filename[MAX_FILENAME_LENGTH + 1] = {'\0',};
};

PokemonHandler newPokemonHandler(const char* filename) {
	std::fstream exists(filename, std::ios::in | std::ios::out | std::ios::app);

	if (!exists) {
		exists.open(filename, std::ios::in | std::ios::out | std::ios::trunc);
	}
	exists.close();

	PokemonHandler ph;
	strncpy(ph.filename, filename, std::min(MAX_FILENAME_LENGTH, strlen(filename)));

	return ph;
}

int size(const PokemonHandler &ph) {
	std::ifstream in(ph.filename, std::ios::in | std::ios::binary);

	if (!in.is_open()) {
		std::cerr << "Error opening file " << ph.filename << " in size(const PokemonHandler &ph)\n";
		exit(1);
	}

    in.seekg(0, std::ios::end);
    int fileSize = in.tellg();

	in.close();
    
    return fileSize / sizeof(Pokemon);
}

Pokemon at(const PokemonHandler &ph, int i) {
    int pokemonCount = size(ph);

	assert(i >= 0 && i < pokemonCount);

	std::ifstream in(ph.filename, std::ios::in | std::ios::binary);

	if (!in.is_open()) {
		std::cerr << "Error opening file " << ph.filename << " in at(const PokemonHandler &ph, int i)\n";
		exit(1);
	}

    in.seekg(i * sizeof(Pokemon), std::ios::beg);
	Pokemon pokemon = readPokemonFromBinaryFile(in);

	in.close();

    return pokemon;
}

void swap(const PokemonHandler &ph, int i, int j) {
	Pokemon first = at(ph, i);
	Pokemon second = at(ph, j);

	std::fstream out(ph.filename, std::ios::out | std::ios::in | std::ios::binary);

	if (!out.is_open()) {
		std::cerr << "Error opening file " << ph.filename << " in swap(const PokemonHandler &ph, int i, int j)\n";
		exit(1);
	}

    out.seekp(i * sizeof(Pokemon), std::ios::beg);
	writePokemonToBinaryFile(out, second);
	out.seekp(j * sizeof(Pokemon), std::ios::beg);
	writePokemonToBinaryFile(out, first);

	out.close();
}

void insert(const PokemonHandler &ph, const Pokemon &pokemon) {
	std::fstream out(ph.filename, std::ios::out | std::ios::in | std::ios::binary | std::ios::ate);

	if (!out.is_open()) {
		std::cerr << "Error opening file " << ph.filename << " in insert(const PokemonHandler &ph, const Pokemon &pokemon)\n";
		exit(1);
	}

	writePokemonToBinaryFile(out, pokemon);

	out.close();

	int i = size(ph) - 1;
	while (i > 0 && at(ph, i - 1).power > at(ph, i).power) {
		swap(ph, i-1, i);
		i--;
	}
}

void textify(const PokemonHandler &ph, const char* filename) {
    std::ofstream out(filename, std::ios::binary);

    if (!out.is_open()) {
		std::cerr << "Error opening file " << filename << " in textify(const PokemonHandler &ph, const char* filename)\n";
		exit(1);
	}

    int pokemonCount = size(ph);
    for (int i = 0; i < pokemonCount; i++) {
		writePokemonToStream(out, at(ph, i));
    }

    out.close();
}

void trunc(const PokemonHandler &ph) {
	std::ofstream out(ph.filename, std::ios::binary | std::ios::trunc);

	if (!out.is_open()) {
		std::cerr << "Error opening file " << ph.filename << " in trunc(const PokemonHandler &ph)\n";
		exit(1);
	}

	out.close();
}

void untextify(const PokemonHandler &ph, const char* filename) {
	std::ifstream in(filename);

    if (!in.is_open()) {
		std::cerr << "Error opening file " << filename << " in untextify(const PokemonHandler &ph, const char* filename)\n";
		exit(1);
	}

	trunc(ph);

	Pokemon pokemon;
	while (readPokemonFromFile(in, pokemon)) {
		insert(ph, pokemon);
	}

	in.close();
}

int main() {
	initTypes();

	PokemonHandler ph = newPokemonHandler("pokemons.dat");

    char cmdLine[MAX_COMMAND_LINE_LENGTH];
	while (std::cin.getline(cmdLine, MAX_COMMAND_LINE_LENGTH)) {
		std::stringstream args(cmdLine);

		char cmd[MAX_COMMAND_LENGTH];
		args >> cmd;

		if (strcmp(cmd, "at") == 0) {
			int i;
			args >> i;

			writePokemonToStream(std::cout, at(ph, i));
		} else if (strcmp(cmd, "size") == 0) {
			std::cout << "Size: " << size(ph) << '\n';
		} else if (strcmp(cmd, "swap") == 0) {
			int i, j;
			args >> i >> j;

			swap(ph, i, j);
		} else if (strcmp(cmd, "insert") == 0) {
			Pokemon pokemon = createPokemonFromConsole();
			insert(ph, pokemon);
		} else if (strcmp(cmd, "textify") == 0) {
			char destination[MAX_FILENAME_LENGTH + 1];
			args >> destination;

			textify(ph, destination);
		} else if (strcmp(cmd, "untextify") == 0) {
			char source[MAX_FILENAME_LENGTH + 1];
			args >> source;

			untextify(ph, source);
		} else if (strcmp(cmd, "exit") == 0) {
			return 0;
		} else {
			std::cout << "==============================\n";
			std::cout << "List of commands:\n";
			std::cout << "size\n";
			std::cout << "at <index>\n";
			std::cout << "swap <index> <index>\n";
			std::cout << "insert\n";
			std::cout << "textify <destination_filename>\n";
			std::cout << "untextify <source_filename>\n";
			std::cout << "exit\n";
			std::cout << "==============================\n";
		}
	}
	
	return 0;
}