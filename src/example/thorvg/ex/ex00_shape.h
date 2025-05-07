#ifndef _TVG_EXAMPLE_SHAPE_H_
#define _TVG_EXAMPLE_SHAPE_H_

#include <string_view>
#include "example.h"

namespace tvgex::example
{

class EX00_Shape : public Example
{
public:
	virtual const std::string& toString() override
	{
		static std::string name = "ex00 shape";
		return name;
	}
	virtual bool content(tvg::Canvas* canvas, uint32_t w, uint32_t h) override
	{
		if (!canvas)
			return false;
		canvas->remove();
		r_canvas_ = canvas;

		// Create a Scene
		scene_ = tvg::Scene::gen();

		rectangle_ = tvg::Shape::gen();
		{
			rectangle_->appendRect(0, 0, 400, 400);	   // x, y, w, h, rx, ry
			rectangle_->fill(0, 255, 0);			   // r, g, b
		}

		roundRectangle_ = tvg::Shape::gen();
		{
			roundRectangle_->appendRect(200, 200, 600, 600, 50, 50);	// x, y, w, h, rx, ry
			roundRectangle_->fill(255, 127, 63);						// r, g, b
		}

		ellipse_ = tvg::Shape::gen();
		{
			ellipse_->appendCircle(600, 600, 150, 100);	   // cx, cy, radiusW, radiusH
			ellipse_->fill(0, 255, 255);				   // r, g, b
		}

		star_ = tvg::Shape::gen();
		{
			// Appends Paths
			star_->moveTo(199, 34);
			star_->lineTo(253, 143);
			star_->lineTo(374, 160);
			star_->lineTo(287, 244);
			star_->lineTo(307, 365);
			star_->lineTo(199, 309);
			star_->lineTo(97, 365);
			star_->lineTo(112, 245);
			star_->lineTo(26, 161);
			star_->lineTo(146, 143);
			star_->close();
			star_->fill(0, 0, 255);
		}

		canvas->push(scene_);

		// gen -> ref = 0
		star_->ref();
		ellipse_->ref();
		rectangle_->ref();
		roundRectangle_->ref();

		bIsDrawRect_ = false;
		bIsDrawEllipse_ = false;
		bIsDrawStar_ = false;
		bIsDrawRoundRect_ = false;

		return true;
	}

	virtual void drawUIWidgets() override
	{
		drawCheckbox("Rect", &rectangle_, &bIsDrawRect_);
		drawCheckbox("Ellipse", &ellipse_, &bIsDrawEllipse_);
		drawCheckbox("Star", &star_, &bIsDrawStar_);
		drawCheckbox("RoundRect", &roundRectangle_, &bIsDrawRoundRect_);
	}
	void drawCheckbox(std::string_view title, tvg::Shape** shape, bool* check)
	{
		if (ImGui::Checkbox(title.data(), check))
		{
			// psuh -> ref++ / remove -> ref--
			if (*check)
				scene_->push(*shape);
			else
				scene_->remove(*shape);
			r_canvas_->update(scene_);
		}
		ImGui::SameLine();
		ImGui::Text("refCount = %d", (*shape)->refCnt());
	}

private:
	bool bIsDrawRect_ = false;
	bool bIsDrawRoundRect_ = false;
	bool bIsDrawEllipse_ = false;
	bool bIsDrawStar_ = false;
	tvg::Canvas* r_canvas_;
	tvg::Scene* scene_;
	tvg::Shape* roundRectangle_;
	tvg::Shape* rectangle_;
	tvg::Shape* ellipse_;
	tvg::Shape* star_;
};

}	 // namespace tvgex::example
#endif
