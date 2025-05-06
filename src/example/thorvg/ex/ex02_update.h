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

	bool update(tvg::Canvas* canvas, double globalTime) override
	{
		if (!canvas)
			return false;

		if (!tvgex::verify(canvas->remove()))
			return false;

		auto progress = tvgex::pingpong(globalTime, 2000.0, true);	 // play time 2 sec.
		SG_LOG_LOG("progress: {}", globalTime);

		// Shape
		auto shape = tvg::Shape::gen();
		shape->appendRect(-100, -100, 200, 200, (100 * progress), (100 * progress));
		shape->fill(rand() % 255, rand() % 255, rand() % 255);
		shape->translate(800 * progress, 800 * progress);
		shape->scale(1.0f - 0.75f * progress);
		shape->rotate(360.0f * progress);

		canvas->push(shape);

		return true;
	}
};

}	 // namespace tvgex::example

#endif
