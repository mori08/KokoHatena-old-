#include "AccessShareData.hpp"
#include "../../RecordManager/RecordManager.hpp"
#include "../../Config/Config.hpp"
#include "../../MyLibrary/MyLibrary.hpp"

#include "Object/Test/TestObject.hpp"
#include "Object/Player/PlayerObject.hpp"

namespace Kokoha
{

	AccessShareData::AccessShareData()
		: m_render(640, 450)
	{
		setMakeObjectFunc<TestObject>  (U"test");
		setMakeObjectFunc<PlayerObject>(U"player");
	}


	void AccessShareData::init()
	{
		m_stageData.init();
		m_lightList.clear();
		m_objectList.clear();
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

		// オブジェクトの追加
		TOMLReader objToml(U"asset/data/stage/object.toml");
		for (const auto& objData : objToml[U"Date" + ToString(date) + U".obj"].tableArrayView())
		{
			const String name = objData[U"type"].getString();
			const Vec2 pos = StageData::squareToPixel(Point(objData[U"pos.x"].get<int32>(), objData[U"pos.y"].get<int32>()));
			m_objectList.emplace_back(m_makeObjectFuncMap[name](pos));	
		}
		return none;
	}


	void AccessShareData::input(const Vec2& cursorPos)
	{
		static const int32 BOARD_HEIGHT = Config::get<int32>(U"Board.controlFrameHeight");

		for (auto& obj : m_objectList)
		{
			obj->input(cursorPos - Vec2(0, BOARD_HEIGHT));
		}
	}


	void AccessShareData::update()
	{
		m_lightList.clear();
		for (auto& obj : m_objectList)
		{
			obj->update(*this);
		}
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

			for (const auto& obj : m_objectList)
			{
				obj->draw();
			}
		}
		Graphics2D::Flush();
		m_render.resolve();
		m_render.draw(0, BOARD_HEIGHT);
	}
}
