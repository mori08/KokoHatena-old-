#include "AccessShareData.hpp"
#include "../../RecordManager/RecordManager.hpp"
#include "../../Config/Config.hpp"
#include "../../MyLibrary/MyLibrary.hpp"


namespace Kokoha
{

	AccessShareData::AccessShareData()
		: m_render(640, 450)
	{

	}


	Optional<String> AccessShareData::load()
	{
		// ���t
		const int32 date = RecordManager::instance().getRecord(U"Date");

		// �n�`�̊O���f�[�^�̕ۑ���
		const FilePath terrainPath 
			= U"asset/data/stage/" + ToString(date) + U".csv";

		// �n�`�̊O���f�[�^(CSV)�̓ǂݍ���
		CSVData terrainCSV(terrainPath);
		if (!terrainCSV)
		{
			return U"Faild to read ["+terrainPath + U"]";
		}

		// StageData�̒n�`��ݒ�
		if (terrainCSV.rows() < StageData::HEIGHT)
		{
			return U"Insufficent rows in [" + terrainPath + U"]";
		}
		for (int32 row = 0; row < StageData::HEIGHT; ++row)
		{
			if (terrainCSV.columns(row) < StageData::WIDTH)
			{
				return U"Insufficent columns in [" + terrainPath + U"]";
			}
			for (int32 column = 0; column < StageData::WIDTH; ++column)
			{
				if (terrainCSV[row][column] == U"1") { m_stageData.setWall(Point(column, row)); }
			}
		}

		// �o�H�T��
		m_stageData.searchPath();

		return none;
	}


	void AccessShareData::update()
	{
	}


	void AccessShareData::draw() const
	{
		static const int32 BOARD_HEIGHT = Config::get<int32>(U"Board.controlFrameHeight");

		m_render.clear(MyBlack);
		{
			ScopedRenderTarget2D target(m_render);

#ifdef _DEBUG
			static bool debugMode = true;
			debugMode ^= Key0.up();

			// �f�o�b�O���ɔ�������ƃ}�X����������`��
			if (debugMode)
			{
				Scene::Rect().draw(Color(MyWhite, 0x40));
				for (int32 i = 0; i < StageData::N; ++i)
				{
					const Point square = StageData::integerToSquare(i);
					Rect(StageData::SQUARE_SIZE * square, StageData::SQUARE_SIZE).drawFrame(1, MyBlack);
				}
			}
#endif // _DEBUG

			m_stageData.draw();
		}
		Graphics2D::Flush();
		m_render.resolve();
		m_render.draw(0, BOARD_HEIGHT);
	}
}
