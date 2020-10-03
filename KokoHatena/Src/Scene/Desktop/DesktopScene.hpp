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

		// �\�����̃{�[�h�̃��X�g
		BoardPtrList m_boardList;

		// ��\���̃{�[�h�̃��X�g
		BoardPtrList m_hideBoardList;

		// �^�X�N�o�[�ɔz�u����{�^��
		std::unordered_map<Board::Role, BoardSymbol> m_boardSymbolMap;

	public:

		DesktopScene(const InitData& init);

	private:

		void update() override;

		void draw() const override;

	private:

		/// <summary>
		/// 
		/// </summary>
		/// <param name="boardItr"></param>
		/// <returns></returns>
		BoardPtrList::iterator moveBoardToTop(BoardPtrList::iterator boardItr);

	};
}