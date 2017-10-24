/*************************************************************************
> File Name: GameAgent.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Hearthstone Game Agent
> Created Time: 2017/09/26
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Agents/GameAgent.h>

namespace Hearthstonepp
{
	GameAgent::GameAgent(User& user1, User& user2, int maxBufferSize)
		: m_userCurrent(user1)
		, m_userOpponent(user2)
		, m_bufferCapacity(maxBufferSize)
		, m_inBuffer(maxBufferSize) // initialize pipe buffer
		, m_outBuffer(maxBufferSize)
		, m_generator(m_rd()) // initialize random generator
	{
		// Do Nothing
	}

	GameAgent::GameAgent(User&& user1, User&& user2, int maxBufferSize)
		: m_userCurrent(std::move(user1))
		, m_userOpponent(std::move(user2))
		, m_bufferCapacity(maxBufferSize)
		, m_inBuffer(maxBufferSize) // initialize pipe buffer
		, m_outBuffer(maxBufferSize)
		, m_generator(m_rd()) // initialize random generator
	{
		// Do Nothing
	}

	std::thread* GameAgent::StartAgent(GameResult& result)
	{
		std::thread *agent = new std::thread([this](GameResult& result) {
			BeginPhase();

			while (!IsGameEnd())
			{
				MainPhase();
			}

			FinalPhase(result);
		}, std::ref(result));

		return agent; // return new GameAgent thread
	}

	void GameAgent::BeginPhase()
	{
		// userCurrent : user who start first
		// userOpponent : user who start later
		DecideDeckOrder();

		ShuffleDeck(m_userCurrent);
		ShuffleDeck(m_userOpponent);

		BeginDraw(m_userCurrent);
		BeginDraw(m_userOpponent);

		Mulligan(m_userCurrent);
		Mulligan(m_userOpponent);

		m_userOpponent.m_hand.push_back(new Card()); // Coin for later user
	}

	void GameAgent::MainPhase()
	{

	}

	void GameAgent::FinalPhase(GameResult& result)
	{
		BYTE end = static_cast<BYTE>(Step::FINAL_GAMEOVER);
		WriteOutputBuffer(&end, 1);
	}

	void GameAgent::DecideDeckOrder()
	{
		// get random number, zero or one.
		std::uniform_int_distribution<int> bin(0, 1);
		if (bin(m_generator) == 1) // swap user with 50% probability
		{
			std::swap(m_userCurrent, m_userOpponent);
		}

		m_userCurrent.m_id = 0;
		m_userOpponent.m_id = 1;

		std::string& userFirst = m_userCurrent.m_player->GetID();
		std::string& userLast = m_userOpponent.m_player->GetID();

		BeginFirstStructure data(userFirst, userLast);
		WriteOutputBuffer((BYTE*)&data, sizeof(BeginFirstStructure));
	}

	void GameAgent::ShuffleDeck(User& user)
	{
		std::vector<Card*>& deck = user.m_deck;
		std::shuffle(deck.begin(), deck.end(), m_generator); // shuffle with random generator

		BeginShuffleStructure data(user.m_id);
		WriteOutputBuffer((BYTE*)&data, sizeof(BeginShuffleStructure));
	}

	void GameAgent::BeginDraw(User& user)
	{
		Draw(user, 3);

		Card** hand = user.m_hand.data();
		DrawStructure data(static_cast<BYTE>(Step::BEGIN_DRAW), user.m_id, 3, 3, hand);
		WriteOutputBuffer((BYTE*)&data, sizeof(DrawStructure));
	}

	void GameAgent::Mulligan(User& user)
	{
		BeginMulliganStructure data(user.m_id);
		WriteOutputBuffer((BYTE*)&data, sizeof(BeginMulliganStructure));

		BYTE index[3] = { 0, };	
		int read = ReadInputBuffer(index, 3); // read index of the card to be mulligan

		std::vector<Card*>& hand = user.m_hand;
		std::sort(index, index + read, std::greater<int>());
		for (int i = 0; i < read; ++i)
		{
			hand.erase(hand.begin() + index[i]); // erase card with given index
		}

		Draw(user, read);
		DrawStructure data2(static_cast<BYTE>(Step::BEGIN_MULLIGAN), user.m_id, read, 3, hand.data());
		WriteOutputBuffer((BYTE*)&data2, sizeof(DrawStructure)); // send new card data
	}

	bool GameAgent::IsGameEnd()
	{
		return true;
		/*
		int healthCurrent = userCurrent.m_hero->health;
		int healthOpponent = userOpponent.m_hero->health;

		if (healthCurrent <= 0 || healthOpponent <= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
		*/
	}

	void GameAgent::Draw(User& user, int num)
	{
		std::vector<Card*>& deck = user.m_deck;
		std::vector<Card*>& hand = user.m_hand;

		for (int i = 0; i < num; ++i)
		{
			hand.push_back(deck.back());
			deck.pop_back();
		}
	}

	int GameAgent::GetBufferCapacity() const
	{
		return m_bufferCapacity;
	}

	int GameAgent::ReadBuffer(BYTE *arr, int maxSize)
	{
		return m_outBuffer.ReadBuffer(arr, maxSize);
	}

	int GameAgent::WriteBuffer(BYTE *arr, int size)
	{
		return m_inBuffer.WriteBuffer(arr, size);
	}

	int GameAgent::ReadInputBuffer(BYTE* arr, int maxSize)
	{
		return m_inBuffer.ReadBuffer(arr, maxSize);
	}

	int GameAgent::WriteOutputBuffer(BYTE* arr, int size)
	{
		return m_outBuffer.WriteBuffer(arr, size);
	}
}