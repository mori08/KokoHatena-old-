#pragma once


#include "../Scene.hpp"
#include "../../BoardShareData/BoardShareData.hpp"
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

		// Board�Ԃ̋��L�f�[�^
		BoardShareData m_boardShareData;

		// �\�����̃{�[�h�̃��X�g
		BoardPtrList m_boardList;

		// ��\���̃{�[�h�̃��X�g
		std::map<Board::Role, std::unique_ptr<Board>> m_hideBoardMap;

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
		/// �^�X�N�o�[�̍���̍��W�̎擾
		/// </summary>
		/// <returns> �^�X�N�o�[�̍���̍��W </returns>
		static const Point& getTaskbarPos()
		{
			static const Point rtn = Point(0, 600 - Kokoha::BoardSymbol::height());
			return rtn;
		}

		/// <summary>
		/// Board�̓o�^
		/// </summary>
		/// <typeparam name="BoardType"> Board�̌^ </typeparam>
		/// <param name="role"> Board�ɑΉ�����Board::Role </param>
		template<typename BoardType>
		void registerBoard(const Board::Role& role, int32 id);

		/// <summary>
		/// Board::Role�ɑΉ�����Board�̃C�e���[�^��T��
		/// </summary>
		/// <param name="role"> Board�ɑΉ�����Board::Role </param>
		/// <returns> �Ή�����C�e���[�^ </returns>
		BoardPtrList::iterator findBoardFromRole(const Board::Role& role);

		/// <summary>
		/// �w�肵��Board���őO�ʂɈړ�
		/// </summary>
		/// <param name="boardItr"> �w�肵��Board�ɑΉ������C�e���[�^ </param>
		/// <returns> ���̃C�e���[�^ </returns>
		BoardPtrList::iterator moveBoardToTop(BoardPtrList::iterator boardItr);

		/// <summary>
		/// Board�̐���
		/// </summary>
		/// <typeparam name="BoardType"> Board�̌^ </typeparam>
		/// <param name="role"> Board�ɑΉ�����Board::Role </param>
		template<typename BoardType>
		void generateBoard(const Board::Role& role);

		/// <summary>
		/// Board�̍폜
		/// </summary>
		/// <param name="boardItr"> �폜����Board�̃C�e���[�^ </param>
		/// <returns> ���̃C�e���[�^ </returns>
		BoardPtrList::iterator eraseBoard(BoardPtrList::iterator boardItr);

		/// <summary>
		/// Board�̔�\��
		/// </summary>
		/// <param name="boardItr"> ��\������Board�̃C�e���[�^ </param>
		/// <returns> ���̃C�e���[�^ </returns>
		BoardPtrList::iterator hideBoard(BoardPtrList::iterator boardItr);

		/// <summary>
		/// Board�̕\��
		/// </summary>
		/// <param name="role"> �\������Board�ɑΉ�����Board::Role </param>
		void displayBoard(Board::Role role);

	};
	



	template<typename BoardType>
	void DesktopScene::registerBoard(const Board::Role& role, int32 id)
	{
		if (m_boardSymbolMap.count(role)) { return; }

		Point pos = getTaskbarPos() + Point(m_boardSymbolMap.size() * BoardSymbol::height(), 0);
		m_boardSymbolMap.try_emplace(role, std::move(BoardSymbol(pos, id)));

		// TODO �֐����
		m_generateBoardMap[role] = [this,role]() { generateBoard<BoardType>(role); };
	}


	template<typename BoardType>
	inline void DesktopScene::generateBoard(const Board::Role& role)
	{
		if (!m_boardList.empty())
		{
			// �����O�ɍőO�ʂɂ���Board�̏�Ԃ�Display�ɕύX
			m_boardSymbolMap.find((*m_boardList.begin())->getRole())->second.setState(BoardSymbol::BoardState::DISPLAYED);
		}

		// �{�[�h�̐���
		m_boardList.emplace_front(std::make_unique<BoardType>(role));

		// �����O�ɍőO�ʂɂ���Board�̏�Ԃ�Top�ɕύX
		m_boardSymbolMap.find((*m_boardList.begin())->getRole())->second.setState(BoardSymbol::BoardState::TOP);
	}

}