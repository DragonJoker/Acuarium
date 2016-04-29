#pragma once

#include "Fish.hpp"
#include "Seaweed.hpp"

namespace aquarium
{
	class NoFoodException
		: public std::exception
	{
	public:
		virtual char const * what() const noexcept
		{
			return "No more food";
		}
	};

	class NoMateException
		: public std::exception
	{
	public:
		virtual char const * what() const noexcept
		{
			return "No mate";
		}
	};

	class WrongMateException
		: public std::exception
	{
	public:
		explicit WrongMateException( Fish & mate )
			: m_mate{ mate }
		{
		}

		virtual char const * what() const noexcept
		{
			return "Mate was not compatible";
		}

		inline Fish const & getMate()const
		{
			return m_mate;
		}

	private:
		Fish & m_mate;
	};
}
