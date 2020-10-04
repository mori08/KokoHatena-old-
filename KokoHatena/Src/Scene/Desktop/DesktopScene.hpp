#pragma once


#include "../Scene.hpp"
#include "../../Board/Board.hpp"
#include "../../BoardSymbol/BoardSymbol.hpp"


namespace Kokoha
{
	/// <summary>
	/// DesktopScene�N���X
	/// Board�̃��X�g���Ǘ�����
	/// </summary>
	class DesktopScene : public MyApp::Scene
	{
	private:

		/// <summary>
		/// Board�̃|�C���^�̃��X�g
		/// </summary>
		using BoardPtrList = std::list<std::unique_ptr<Board>>;

	private:

		// �^�X�N�o�[�̉E��̍��W
		static const Point TASKBAR_POS;

		// �\�����̃{�[�h�̃��X�g
		BoardPtrList m_boardList;

		// ��\���̃{�[�h�̃��X�g
		BoardPtrList m_hideBoardList;

		// �^�X�N�o�[�ɔz�u����{�^��
		std::unordered_map<Board::Role, BoardSymbol> m_boardSymbolMap;

		// Board�����p�̘A�z�z��
		std::unordered_map<Board::Role, std::function<void()>> m_generateBoardMap;

	public:

		DesktopScene(const InitData& init);

	private:

		void update() override;

		void draw() const override;

	private:

		/// <summary>
		/// Board�̓o�^
		/// </summary>
		/// <typeparam name="BoardType"> Board�̌^ </typeparam>
		/// <param name="role"> Board�ɑΉ�����Board::Role </param>
		template<typename BoardType>
		void registerBoard(const Board::Role& role, int32 id);

		/// <summary>
		/// �w�肵��Board���őO�ʂɈړ�
		/// </summary>
		/// <param name="boardItr"> �w�肵��Board�ɑΉ������C�e���[�^ </param>
		/// <returns> ���̃C�e���[�^ </returns>
		BoardPtrList::iterator moveBoardToTop(BoardPtrList::iterator boardItr);

	};
	

	template<typename BoardType>
	void DesktopScene::registerBoard(const Board::Role& role, int32 id)
	{
		if (m_boardSymbolMap.count(role)) { return; }

		Point pos = TASKBAR_POS + Point(m_boardSymbolMap.size() * BoardSymbol::SIZE, 0);
		m_boardSymbolMap.try_emplace(role, std::move(BoardSymbol(pos, id)));

		// TODO �֐����
		m_generateBoardMap[role] = []() {};
	}

}