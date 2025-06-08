#ifndef _TVG_EXAMPLE_03_REGION_H_
#define _TVG_EXAMPLE_03_REGION_H_

#include <editor/app.h>
#include "example.h"
#include <random>
#include "algorithm/dirtyRegion.h"

namespace tvgex::example
{

struct DirtyRegion
{
	void add(const Region& region)
	{
		input.push_back(region);
	}
	const Regions& result()
	{
		return output;
	}
	void run(DirtyRegionAlgorithm* func)
	{
		output = func->run(input);
	}
	void clear()
	{
		input.clear();
	}

	Regions input;
	Regions output;
};

constexpr const size_t INPUT_COUNT = 5;
constexpr const size_t WIDTH = 1000;
constexpr const size_t HEIGHT = 1000;
constexpr const size_t MAX_SIZE = 250;
constexpr const size_t MIN_SIZE = 100;

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<> x1Rand(1, WIDTH - MAX_SIZE);
static std::uniform_int_distribution<> y1Rand(1, HEIGHT - MAX_SIZE);
static std::uniform_int_distribution<> sizeRand(MIN_SIZE, MAX_SIZE);

class DirtyRegionTest
{
public:
	enum AlgorithmType
	{
		SIMPLE_SPLIT_AND_MERGE = 0,
		SIMPLE_SPLIT = 1,
		SIMPLE_SPLIT2 = 2,
		SIMPLE_SPLIT2_AND_MERGE = 3,
		SIMPLE_SPLIT2_X = 4,
	};
	DirtyRegionTest()
	{
		init(INPUT_COUNT);
		dirtyRegionAlgorithms_.push_back(new SimpleSplitAndMerge());
		dirtyRegionAlgorithms_.push_back(new SimpleSplit());
		dirtyRegionAlgorithms_.push_back(new SimpleSplit2());
		dirtyRegionAlgorithms_.push_back(new SimpleSplit2AndMerge());
		dirtyRegionAlgorithms_.push_back(new SimpleSplit2_X());
	}
	void init(int inputCount)
	{
		region_.clear();
		for (auto i = 0; i < inputCount; ++i)
		{
			size_t x1 = x1Rand(gen);
			size_t y1 = y1Rand(gen);
			size_t x2 = x1 + sizeRand(gen);
			size_t y2 = y1 + sizeRand(gen);

			region_.add({x1, y1, x2, y2});
			printf("input: %zu %zu %zu %zu\n", x1, y1, x2, y2);
		}
	}
	void run(AlgorithmType type)
	{
		region_.run(dirtyRegionAlgorithms_[type]);
	}
	const Regions& input()
	{
		return region_.input;
	}
	const Regions& output()
	{
		return region_.output;
	}
	void clearOutput()
	{
		region_.output.clear();
	}

private:
	DirtyRegion region_;
	std::vector<DirtyRegionAlgorithm*> dirtyRegionAlgorithms_;
};

class EX03_Region : public Example
{
public:
	void outputLine(tvg::Scene* scene, const Region& region, int idx)
	{
		auto x = region.x1;
		auto y = region.y1;
		auto w = region.x2 - region.x1;
		auto h = region.y2 - region.y1;
		auto bound = tvg::Shape::gen();
		bound->moveTo(x, y);
		bound->lineTo(x + w, y);
		bound->lineTo(x + w, y + h);
		bound->lineTo(x, y + h);
		bound->close();
		bound->strokeWidth(5.0f);
		bound->strokeFill(255, 0, 0, 255);
		scene->push(bound);
		{
			auto text = tvg::Text::gen();
			text->font("Arial", 50);
			text->text(std::to_string(idx).c_str());
			text->fill(255, 0, 0);
			text->translate(x -30, y);
			text->scale(0.5f);
			scene->push(text);

			auto text2 = tvg::Text::gen();
			text2->font("Arial", 50);
			text2->text(std::to_string(idx).c_str());
			text2->fill(0, 255, 0);
			text2->translate(x + w - 30, y + h - 50);
			text2->scale(0.5f);
			scene->push(text2);
		}
	}
	const std::string& toString() override
	{
		static std::string name = "ex03 region";
		return name;
	}
	bool content(tvg::Canvas* canvas, uint32_t w, uint32_t h) override
	{
		if (!canvas)
			return false;
		if (!verify(tvg::Text::load("./resources/font/Arial.ttf")))
			return false;

		inputController_ = std::make_unique<ns::InputController>();

		inputController_->bindAction(ns::InputAction(ns::InputType::MOUSE_LEFT_DOWN), ns::InputTrigger::Started, this,
									 &EX03_Region::moveRegionStart);
		inputController_->bindAction(ns::InputAction(ns::InputType::MOUSE_LEFT_DOWN), ns::InputTrigger::Ended, this,
									 &EX03_Region::moveRegionEnd);
		inputController_->bindAction(ns::InputAction(ns::InputType::MOUSE_LEFT_DOWN), ns::InputTrigger::Triggered, this,
									 &EX03_Region::moveRegion);
		inputController_->bindAction(ns::InputAction(ns::InputType::MOUSE_MOVE), ns::InputTrigger::Triggered, this,
									 &EX03_Region::pickCurRegion);
		inputController_->bindAction(ns::InputAction(ns::InputType::MOUSE_WHEEL), ns::InputTrigger::Triggered, this,
									 &EX03_Region::scaleRegion);
		ns::editor::App::SetCurrentInputController(inputController_.get());

		return true;
	}
	void moveRegionStart(const ns::InputValue& value)
	{
		bIsMouseDrag_ = true;
		if (currentRegion_ == -1)
			return;
		beforeMousePos_ = value.get<ns::Vec3>() / zoom_;
		auto& regions = const_cast<Regions&>(test_.input());
		beforeRegion_ = regions[currentRegion_];
		wheelScale = 1.0f;
	}
	void moveRegion(const ns::InputValue& value)
	{
		if (currentRegion_ == -1)
			return;
		auto pos = value.get<ns::Vec3>() / zoom_;
		auto& regions = const_cast<Regions&>(test_.input());
		auto deltaX = pos.x - beforeMousePos_.x;
		auto deltaY = pos.y - beforeMousePos_.y;

		wheelScale = std::min(3.0f, std::max(0.1f, wheelScale));
		regions[currentRegion_] = scale(beforeRegion_, wheelScale);

		auto width = regions[currentRegion_].x2 - regions[currentRegion_].x1;
		auto height = regions[currentRegion_].y2 - regions[currentRegion_].y1;

		regions[currentRegion_].x1 = regions[currentRegion_].x1 + deltaX;
		regions[currentRegion_].y1 = regions[currentRegion_].y1 + deltaY;
		regions[currentRegion_].x2 = regions[currentRegion_].x1 + width;
		regions[currentRegion_].y2 = regions[currentRegion_].y1 + height;

		NS_LOG("x {}, y {}, width {}, height {}", regions[currentRegion_].x1, regions[currentRegion_].y1, width,
			   height);
	}
	void moveRegionEnd(const ns::InputValue& value)
	{
		bIsMouseDrag_ = false;
		wheelScale = 1.0f;
	}
	int pickRegion(float x, float y)
	{
		auto regions = const_cast<Regions&>(test_.input());
		for (int i = 0; i < regions.size(); ++i)
		{
			if (checkContain(x, y, regions[i]))
			{
				return i;
			}
		}
		return -1;
	}
	void pickCurRegion(const ns::InputValue& value)
	{
		if (bIsMouseDrag_)
			return;
		auto pos = value.get<ns::Vec3>() / zoom_;
		currentRegion_ = pickRegion(pos.x, pos.y);
	}
	void scaleRegion(const ns::InputValue& value)
	{
		if (bIsMouseDrag_ == false || currentRegion_ == -1)
			return;
		auto pos = value.get<ns::Vec3>();
		auto regions = const_cast<Regions&>(test_.input());
		wheelScale += pos.x / 50.0f;
		wheelScale = std::max(0.1f, wheelScale);
	}

	bool update(tvg::Canvas* canvas, double deltaTime) override
	{
		if (!canvas)
			return false;

		if (!verify(canvas->remove()))
			return false;

		auto scene = tvg::Scene::gen();

		int regionLabel = 0;
		for (const auto& region : test_.input())
		{
			auto x = region.x1;
			auto y = region.y1;
			auto width = region.x2 - region.x1;
			auto height = region.y2 - region.y1;
			{
				auto shape = tvg::Shape::gen();
				shape->appendRect(x, y, width, height);
				shape->fill(200, 150, 200);
				shape->opacity(200);
				scene->push(shape);
			}
			{
				auto text = tvg::Text::gen();
				text->font("Arial", 50);
				text->text(std::to_string(regionLabel).c_str());
				text->fill(255, 255, 255);
				text->translate(x, y);
				text->scale(1.0f);
				scene->push(text);
				regionLabel++;
			}
		}

		// start test
		test_.clearOutput();
		timer_.reset();
		test_.run(static_cast<DirtyRegionTest::AlgorithmType>(algorithmType_));
		totalTestTime_ += timer_.elapsed();
		testCount_++;

		// draw output
		if (bIsDrawOutput_)
		{
			for (int i = 0; i < test_.output().size(); i++)
			{
				outputLine(scene, test_.output().at(i), i);
			}
		}
		scene->scale(zoom_);
		canvas->push(scene);

		return true;
	}
	virtual void drawUIWidgets() override
	{
		// prevent overflow
		bool bIsTestCountInit = testCount_ < 0;
		if (ImGui::Button("reset"))
		{
			bIsTestCountInit = true;
			test_.init(inputCount_);
		}
		if(testCount_ > 0)
			ImGui::Text("average run time: %f ms",totalTestTime_/testCount_);
		ImGui::Checkbox("draw output", &bIsDrawOutput_);
		bIsTestCountInit |= ImGui::RadioButton("Simple Split", &algorithmType_, DirtyRegionTest::AlgorithmType::SIMPLE_SPLIT);
		bIsTestCountInit |= ImGui::RadioButton("Simple Split And Merge", &algorithmType_, DirtyRegionTest::AlgorithmType::SIMPLE_SPLIT_AND_MERGE);
		bIsTestCountInit |= ImGui::RadioButton("Simple Split2 And Merge", &algorithmType_, DirtyRegionTest::AlgorithmType::SIMPLE_SPLIT2_AND_MERGE);
		bIsTestCountInit |= ImGui::RadioButton("Simple Split2", &algorithmType_, DirtyRegionTest::AlgorithmType::SIMPLE_SPLIT2);
		bIsTestCountInit |= ImGui::RadioButton("Simple Split2_x", &algorithmType_, DirtyRegionTest::AlgorithmType::SIMPLE_SPLIT2_X);
		ImGui::DragFloat("zoom", &zoom_, 0.01f, 0.1f, 1.0f);
		ImGui::DragInt("inputSize", &inputCount_, 1, 1, 50);

		if(bIsTestCountInit)
		{
			totalTestTime_ = 0.0;
			testCount_ = 0;
		}

		for(int i = 0; i < test_.output().size(); i++ )
		{
			auto region = test_.output().at(i);
			ImGui::Text("%03d: x: %04zu, y: %04zu, x2: %04zu, y2: %04zu", i, region.x1, region.y1, region.x2, region.y2);
		}
	}
	virtual void resize(const ns::Resolution& res)
	{
		res_ = res;
		if (res.height > res.width)
			zoom_ = (float) res.width / (float) WIDTH;
		else
			zoom_ = (float) res.height / (float) HEIGHT;
	}

private:
	ns::Resolution res_;
	DirtyRegionTest test_;

	// for perfomance
	ns::Timer timer_{};
	double totalTestTime_{0.0};
	int testCount_ = 0;

	// for gui option
	bool bIsDrawOutput_{true};
	int algorithmType_{0};
	float zoom_{1.0f};
	int inputCount_=INPUT_COUNT;

	// input
	ns::Vec3 beforeMousePos_;
	int currentRegion_{0};
	Region beforeRegion_;
	bool bIsMouseDrag_{false};
	float wheelScale = 1.0f;
};

}	 // namespace tvgex::example

#endif