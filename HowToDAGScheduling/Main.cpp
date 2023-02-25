# include <Siv3D.hpp> // OpenSiv3D v0.6.6
# include "DAG.h"
# include "SchedGrid.h"
# include "Compiler.h"
# include "DAGJsonReader.h"

void Main()
{
	// 背景の色を設定 | Set background color
	Scene::SetBackground(Palette::Lightgreen);

	DAG dag = DAGJsonReader::generate_dag(U"sample_dag.json");
	SchedGrid grid;
	Compiler compiler;

	while (System::Update())
	{
		dag.update();
		if (MouseL.up())
			dag.fit(grid);
		if (SimpleGUI::Button(U"COMPILE", Vec2(600, 300)))
		{
			compiler.compile(dag, grid);
		}
		if (MouseR.down())
		{
			compiler.compile(dag, grid);
		}
		dag.draw();
		grid.draw();
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要です。
//
// チュートリアル
// https://siv3d.github.io/ja-jp/tutorial/tutorial/
//
// Tutorial
// https://siv3d.github.io/tutorial/tutorial/
//
// Siv3D コミュニティへの参加（Discord などで気軽に質問や交流, 最新情報の入手ができます）
// https://siv3d.github.io/ja-jp/community/community/
//
// Siv3D User Community
// https://siv3d.github.io/community/community/
//
// 新機能の提案やバグの報告 | Feedback
// https://siv3d.github.io/ja-jp/develop/report/
//
// Sponsoring Siv3D
// https://github.com/sponsors/Reputeless
//
