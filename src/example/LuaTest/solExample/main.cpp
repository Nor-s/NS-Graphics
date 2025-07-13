#include <sol/sol.hpp>
#include <iostream>

int main()
{
	sol::state lua;
	sol::protected_function pf;
	for (int i = 0; i < 1000; i++)
	{
		auto result =
			lua.safe_script("function compute(i, j, k) i= i+j if  i>0 then return -11 end return i + j + k end",
							sol::script_pass_on_error);
		int a;
		if (result.valid())
		{
			auto f = lua.get<sol::function>("compute");
		 	pf = f;
			sol::protected_function_result pfr = pf(1, 2, 3);
			if (pfr.valid())
			{
				a = pfr;
			}
		}
	}

	sol::protected_function_result pfr = pf(1, 2, 100);
	int k = pfr;

	

	return 0;
}