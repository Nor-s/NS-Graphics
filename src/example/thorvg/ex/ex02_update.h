/*
 * Copyright (c) 2020 - 2025 the ThorVG project. All rights reserved.

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef _TVG_EXAMPLE_UPDATE_H_
#define _TVG_EXAMPLE_UPDATE_H_

#include "example.h"

namespace tvgex::example
{
class EX02_Update : public Example
{
public:
	const std::string& toString() override
	{
		static std::string name = "ex02 update";
		return name;
	}
	bool content(tvg::Canvas* canvas, uint32_t w, uint32_t h) override
	{
		if (!canvas)
			return false;

		// Shape
		auto shape = tvg::Shape::gen();
		shape->appendRect(-100, -100, 200, 200);
		shape->fill(255, 255, 255);
		canvas->push(shape);

		return true;
	}

	bool update(tvg::Canvas* canvas, double deltaTime) override
	{
		if (!canvas)
			return false;

		if (!tvgex::verify(canvas->remove()))
			return false;


		progress_ = static_cast<float>(tvgex::pingpong(animationTime_, animationDuration_, true));	  // play time 2 sec.

		// Shape
		auto shape = tvg::Shape::gen();
		shape->appendRect(-100, -100, 200, 200, (100 * progress_), (100 * progress_));
		shape->fill(rand() % 255, rand() % 255, rand() % 255);
		shape->translate(800 * progress_, 800 * progress_);
		shape->scale(1.0f - 0.75f * progress_);
		shape->rotate(360.0f * progress_);

		canvas->push(shape);
		animationTime_ += static_cast<float>(deltaTime);
		deltaTime_ = static_cast<float>(deltaTime);

		return true;
	}
	virtual void drawUIWidgets() override
	{
		bool bIsDec = static_cast<int>(animationTime_/animationDuration_)%2 == 1;
		bool change = false;

		ImGui::Text("animationTime %f, delta: %f",animationTime_, deltaTime_);

		ImGui::ProgressBar(progress_, ImVec2(0.0f, 0.0f));
		change |= ImGui::SliderFloat("Duration", &animationDuration_, 1000.0f, 10000.0f);
		change |= ImGui::SliderFloat("Progress", &progress_, 0.0f, 1.0f);

		if(change)
		{
			if(bIsDec)
				animationTime_ = (1.0-progress_) * animationDuration_ + animationDuration_;
			else
				animationTime_ = progress_ * animationDuration_;
		}
	}

private:
	float animationTime_ = 0.0f;
	float animationDuration_ = 2000.0f;
	float deltaTime_ = 0.0f;
	float progress_ = 0.0f;
};

}	 // namespace tvgex::example

#endif
