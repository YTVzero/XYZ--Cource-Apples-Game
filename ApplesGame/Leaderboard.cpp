#include "Leaderboard.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

namespace CatAndApples
{
	Leaderboard::Leaderboard()
	{
		GenerateFakeData();
	}

	void Leaderboard::UpdateSortedRecords()
	{
		sortedRecords.clear();
		for (const auto& pair : records)
		{
			sortedRecords.push_back({ pair.first, pair.second });
		}
		SortRecords();

		if (sortedRecords.size() > maxEntries)
		{
			sortedRecords.resize(maxEntries);
		}
	}

	void Leaderboard::AddRecord(const std::string& name, int score)
	{
		records[name] = score;
		UpdateSortedRecords();
	}

	void Leaderboard::UpdatePlayerScore(const std::string& name, int newScore, bool addToExisting)
	{
		if (addToExisting && records.find(name) != records.end()) {
			records[name] += newScore;
		}
		else {
			records[name] = newScore;
		}
		UpdateSortedRecords();
	}

	void Leaderboard::GenerateFakeData()
	{

		const std::string names[] = { "Goblin","Robin","Hoblin","Groblin","Jorgi"};

		for (int i = 0; i < 5; ++i)
		{
			int randomScore = 30 + (rand() % 150);
			records[names[i]] = randomScore;
		}

		UpdateSortedRecords ();
	
	}

	void Leaderboard::SortRecords()
	{
		for (size_t i = 1; i < sortedRecords.size(); ++i)
		{
			Record key = sortedRecords[i];
			int j = i - 1;

			while (j >= 0 && sortedRecords[j].score < key.score)
			{
				sortedRecords[j + 1] = sortedRecords[j];
				j = j - 1;
			}
			sortedRecords[j + 1] = key;
		}
	}

	void Leaderboard::Clear()
	{
		records.clear();
		sortedRecords.clear();
	}
	
}