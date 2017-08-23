/*************************************************************************
> File Name: Card.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Card class that stores card information.
> Created Time: 2017/08/21
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_CARD_H
#define HEARTHSTONEPP_CARD_H

#include <Enchants/Enchantment.h>
#include <Enums/Enums.h>

#include <map>
#include <string>
#include <vector>

namespace Hearthstonepp
{
	class Card
	{
	private:
		int m_assetID;
		int m_id;
		std::string m_name;
		std::string m_text;
		std::vector<std::string> m_entourage; // �ֺ� �ϼ���
		std::map<GameTag, int> m_tags; // ��������
		std::map<GameTag, int> m_refTags;
		std::map<PlayReq, int> m_playRequirements; // �÷��� �䱸 ����
		bool m_isCollectible; // ȸ�� ���� ����
		Race m_race; //����
		Faction m_faction; // ȣ�� or ���
		bool m_hasCombo; // ����
		bool m_rarity; // ��͵�
		CardType m_type; // ī�� ����
		CardSet m_set; // 
		int m_cost; // �ڽ�Ʈ
		bool m_hasOverload; // ����ȭ
		int m_overload; // ����ȭ �ڽ�Ʈ
		bool m_requiresTarget;
		bool m_requiresTargetForCombo;
		bool m_requiresTargetIfAvailable;
		bool m_requiresTargetIfAvailableAndDragonInHand; // �ڵ忡 ������ ���� ��
		bool m_requiresTargetIfAvailableAndElementalPlayedLastTurn;
		bool m_requiresTargetIfAvailableAndMinimumFriendlyMinions;
		bool m_requiresTargetIfAvailableAndMinimumFriendlySecrets;
		int m_maxAllowedInDeck; // ���� �ִ�� ���� �� �ִ� ī�� ��
		bool m_isImplemented; // �����Ǿ��ִ� Ŭ��������
		std::vector<Enchantment> m_enchantments; // ī�忡 �ο��� ȿ�� ���
		bool m_isAffectedBySpellDamage; // �ֹ� ī��� ���ظ� �Ծ�����
		int m_multiClassGroup;
	};
}

#endif