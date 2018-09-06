//
//  HapticFeedback.h
//  iSSB
//
//  Created by Luis Finke on 9/6/18.
//  Copyright © 2018 Luis Finke. All rights reserved.
//

#pragma once

namespace GameEngine
{
	class HapticFeedback
	{
	public:
		static bool initialize();
		
		static void buzz(long milliseconds, float strength);
	};
}
