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

#ifdef _DEBUG
			static bool debugMode = true;
			debugMode ^= Key0.up();

			// デバッグ時に薄い明りとマスを示す線を描画
			if (debugMode)
			{
				Scene::Rect().draw(Color(MyWhite, 0x20));
				for (int32 i = 0; i < StageData::N; ++i)
				{
					const Point square = StageData::integerToSquare(i);
					Rect(StageData::SQUARE_SIZE * square, StageData::SQUARE_SIZE).drawFrame(1, MyBlack);
				}
			}
#endif // _DEBUG

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
