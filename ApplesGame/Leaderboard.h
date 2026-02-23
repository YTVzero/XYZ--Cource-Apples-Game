#pragma once
#include <string>
#include <unordered_map>
#include <vector>

namespace CatAndApples
{
	struct Record
	{
		std::string name;
		int score = 0;
	};

	class Leaderboard
	{
	private:
		std::unordered_map<std::string, int>records;
		std::vector<Record> sortedRecords;
		const int maxEntries = 5;

		void UpdateSortedRecords();

	public:
		Leaderboard();

		void AddRecord(const std::string& name, int score);
		void UpdatePlayerScore(const std::string& name, int newScore, bool addToExisting = true);
		void GenerateFakeData();
		const std::vector<Record>& GetSortedRecords() const {
			return sortedRecords;
		}
		void SortRecords();
		void Clear();
	};
}