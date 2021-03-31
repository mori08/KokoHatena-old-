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


	void AccessShareData::init()
	{
		m_stageData.init();
	}


	Optional<String> AccessShareData::load()
	{
		// ������
		init();

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

		// ��Q���̂܂Ƃ�
		m_stageData.makeBlockList();

		return none;
	}


	void AccessShareData::update()
	{
		m_lightList.clear();
		static double direction = 0.2 * Math::Pi;
		static double goalDire = 0.2 * Math::Pi;
		internalDividingPoint(direction, goalDire, 0.1);
		static Point pos(230,140);
		goalDire += 0.1 * Math::Pi * Mouse::Wheel();
		pos += Point(KeyD.pressed() - KeyA.pressed(), KeyS.pressed() - KeyW.pressed());
		pos += Point(KeyRight.up() - KeyLeft.up(), KeyDown.up() - KeyUp.up());

		static double direction2 = 0;

		m_lightList.emplace_back(Circle(pos, 200), direction, Math::Pi / 6);
		//m_lightList.emplace_back(Circle(570,420, 400), 2*Scene::Time(), Math::Pi / 6);
	}


	void AccessShareData::draw() const
	{
		static const int32 BOARD_HEIGHT = Config::get<int32>(U"Board.controlFrameHeight");

		m_render.clear(MyBlack);
		{
			ScopedRenderTarget2D target(m_render);

			m_stageData.draw();

			for (const auto& light : m_lightList)
			{
				light.draw(m_stageData);
			}
		}
		Graphics2D::Flush();
		m_render.resolve();
		m_render.draw(0, BOARD_HEIGHT);
	}
}
