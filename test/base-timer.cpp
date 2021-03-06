/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012-present Icinga Development Team (http://www.icinga.org) *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#include "base/timer.h"
#include "base/utility.h"
#include "base/application.h"
#include <boost/test/unit_test.hpp>
#include <boost/foreach.hpp>

using namespace icinga;

struct TimerFixture
{
	TimerFixture(void)
	{
		Timer::Initialize();
	}

	~TimerFixture(void)
	{
		Timer::Uninitialize();
	}
};

BOOST_FIXTURE_TEST_SUITE(base_timer, TimerFixture)

BOOST_AUTO_TEST_CASE(construct)
{
	Timer::Ptr timer = make_shared<Timer>();
	BOOST_CHECK(timer);
}

BOOST_AUTO_TEST_CASE(interval)
{
	Timer::Ptr timer = make_shared<Timer>();
	timer->SetInterval(1.5);
	BOOST_CHECK(timer->GetInterval() == 1.5);
}

static void Callback(int *counter)
{
	(*counter)++;
}

BOOST_AUTO_TEST_CASE(invoke)
{
	int counter;
	Timer::Ptr timer = make_shared<Timer>();
	timer->OnTimerExpired.connect(boost::bind(&Callback, &counter));
	timer->SetInterval(1);

	counter = 0;
	timer->Start();
	Utility::Sleep(5.5);
	timer->Stop();

	BOOST_CHECK(counter >= 4 && counter <= 6);
}

BOOST_AUTO_TEST_CASE(scope)
{
	int counter;
	Timer::Ptr timer = make_shared<Timer>();
	timer->OnTimerExpired.connect(boost::bind(&Callback, &counter));
	timer->SetInterval(1);

	counter = 0;
	timer->Start();
	Utility::Sleep(5.5);
	timer.reset();
	Utility::Sleep(5.5);

	BOOST_CHECK(counter >= 4 && counter <= 6);
}

BOOST_AUTO_TEST_SUITE_END()
