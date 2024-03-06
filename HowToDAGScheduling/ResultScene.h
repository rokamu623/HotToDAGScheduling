#pragma once
#include <Siv3D.hpp>
#include "SceneName.h"
#include "BGMManager.h"
#include "SEManager.h"
#include "DAGJsonPackage.h"
#include "Layout.h"

// リザルト表示
class ResultDisplay
{
private:
	Rect _field;
	Font _font;
	String _text;
	Color _color;

public:
	ResultDisplay() {};
	ResultDisplay(FilePath path);

	void draw() const;
};

// 各ステージのリザルトGUI
class ResultStage
{
private:
	FilePath _path;
	String _name;

	Point _pos;
	Quad _body;
	bool _over;
	Font _font;

public:
	ResultStage() {};
	ResultStage(FilePath path, Point pos);

	void update();
	void draw() const;

	Quad body() { return _body; };
	FilePath path() { return _path; };
};

class ResultScene : public App::Scene
{
private:
	Array<ResultStage> _stages;

	Point _select_button_pos;

	Optional<ResultDisplay> _display;

public:
	ResultScene(const InitData& init);

	void update();
	void draw() const;
};

