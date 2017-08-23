/*************************************************************************
> File Name: Hearo.h
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Hero class that stores hero information.
> Created Time: 2017/08/21
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_HERO_H
#define HEARTHSTONEPP_HERO_H

#include <Enchants/Enchantment.h>
#include <Enums/Enums.h>
#include <Models/Card.h>

#include <map>
#include <string>
#include <vector>

namespace Hearthstonepp 
{
	class Hero
	{
	private:
		int m_assetID;
		int m_id;
		std::string m_name;
		Race m_race; //����
		Faction m_faction; // ȣ�� or ���
		std::map<GameTag, int> m_tags; // ��������
		std::map<GameTag, int> m_refTags;
		std::map<PlayReq, int> m_playRequirements; // �÷��� �䱸 ����
		int m_health;
		int m_armor;
		int m_attack;
		bool m_isEquippedWithWeopon; // ���� ���� ����
		Card m_refWepon; // ���� ���۷���
		HeroPower m_heroPower; // ���� �ɷ�
		std::vector<Enchantment> m_enchantments; // ī�忡 �ο��� ȿ�� ���
		bool m_isImplemented; // �����Ǿ��ִ� Ŭ��������

		// std::vector<std::string> m_entourage; // �ֺ� �ϼ���
		// bool m_isCollectible; // ȸ�� ���� ����
		// bool m_hasCombo; // ����
		// bool m_rarity; // ��͵�
		// CardType m_type; // ī�� ����
		// CardSet m_set; // 
		// int m_cost; // �ڽ�Ʈ
		// bool m_hasOverload; // ����ȭ
		// int m_overload; // ����ȭ �ڽ�Ʈ
		// bool m_requiresTarget;
		// bool m_requiresTargetForCombo; 
		// bool m_requiresTargetIfAvailable;
		// bool m_requiresTargetIfAvailableAndDragonInHand; // �ڵ忡 ������ ���� ��
		// bool m_requiresTargetIfAvailableAndElementalPlayedLastTurn; // ���� �Ͽ� ������ ���� ��
		// bool m_requiresTargetIfAvailableAndMinimumFriendlyMinions; // �ʵ� ��ü�� n ���� �̻��� ��
		// bool m_requiresTargetIfAvailableAndMinimumFriendlySecrets; // ����� �ɷ� �ִ°�
		// bool m_isAffectedBySpellDamage; // �ֹ� ī��� ���ظ� �Ծ�����
		// int m_maxAllowedInDeck; // ���� �ִ�� ���� �� �ִ� ī�� ��
		// int m_multiClassGroup;
	};

	class HeroPower
	{
	private:

	};
}

#endif