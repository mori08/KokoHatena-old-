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
		// 初期化
		init();

		// 日付
		const int32 date = RecordManager::instance().getRecord(U"Date");

		// 地形の外部データの保存先
		const FilePath terrainPath 
			= U"asset/data/stage/" + ToString(date) + U".csv";

		// 地形の外部データ(CSV)の読み込み
		CSVData terrainCSV(terrainPath);
		if (!terrainCSV)
		{
			return U"Faild to read ["+terrainPath + U"]";
		}

		// StageDataの地形を設定
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

		// 経路探索
		m_stageData.searchPath();

		// 障害物のまとめ
		m_stageData.makeBlockList();

		return none;
	}


	void AccessShareData::update()
	{
		m_lightList.clear();
		static double direction = 0.2 * Math::Pi;
		static double goalDire = 0.2 * Math::Pi;
		static double angle = Math::Pi / 6;
		internalDividingPoint(direction, goalDire, 0.1);
		angle += (KeyQ.up() - KeyE.up()) * 0.1 * Math::Pi;
		angle = Clamp(angle, 0.0, Math::Pi);
		static Point pos(1,1);
		goalDire += 0.1 * Math::Pi * Mouse::Wheel();
		pos += Point(KeyD.pressed() - KeyA.pressed(), KeyS.pressed() - KeyW.pressed());
		pos += Point(KeyRight.up() - KeyLeft.up(), KeyDown.up() - KeyUp.up());

		m_lightList.emplace_back(Circle(pos, 200), direction, angle);
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
