#pragma once
#include <Siv3D.hpp>

namespace LAYOUT
{

	const Point MERGIN = Point(10, 10);
	const int STAZE_SPACE_HEIGHT = 20;
	const Point WINDOW_SIZE = Point(800, 600);
	const Point DAG_SPACE_SIZE = (Vec2(WINDOW_SIZE - MERGIN * 3 - Point(0, STAZE_SPACE_HEIGHT)) * Vec2(0.4, 0.5)).asPoint();
	const Point CONSOLE_SPACE_SIZE = (Vec2(WINDOW_SIZE - MERGIN * 3 - Point(0, STAZE_SPACE_HEIGHT)) * Vec2(0.6, 0.5)).asPoint();
	const Point SCHED_SPACE_SIZE = (Vec2(WINDOW_SIZE - MERGIN * 3 - Point(0, STAZE_SPACE_HEIGHT)) * Vec2(0.6, 0.5)).asPoint();
	const Point SPACE_SPACE_SIZE = (Vec2(WINDOW_SIZE - MERGIN * 3 - Point(0, STAZE_SPACE_HEIGHT)) * Vec2(0.4, 0.5)).asPoint();

	const Color FIELD_COLOR = Palette::Lightgray;
}
