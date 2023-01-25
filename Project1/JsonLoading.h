#pragma once
#ifndef JSONLOADING_H
#define JSONLOADING_H

#include <fstream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class JsonLoading
{
public:
	template <typename t>
	static void LoadJson(std::vector<t>& structData, std::string inputfile);
	template <typename t>
	static void SaveJson(std::vector<t> structData, std::string inputfile);
	template <typename t>
	static void LoadJson(t& structData, std::string inputfile);
	template <typename t>
	static void SaveJson(t structData, std::string inputfile);
};

//Dont put these in the cpp, it will brake
template<typename t>
static void JsonLoading::LoadJson(std::vector<t>& structData, std::string inputfile)
{
	std::ifstream jsonFile(inputfile);
	json jsonData = json::parse(jsonFile);
	structData = jsonData;
}

template<typename t>
static void JsonLoading::SaveJson(std::vector<t> structData, std::string inputfile)
{
	json jsonData = structData;
	std::ofstream myFile(inputfile);
	myFile << std::setw(4) << jsonData << std::endl;
}

template<typename t>
static void JsonLoading::LoadJson(t& structData, std::string inputfile)
{
	std::ifstream jsonFile(inputfile);
	json jsonData = json::parse(jsonFile);
	structData = jsonData;
}

template<typename t>
static void JsonLoading::SaveJson(t structData, std::string inputfile)
{
	json jsonData = structData;
	std::ofstream myFile(inputfile);
	myFile << std::setw(4) << jsonData << std::endl;
}


#endif
