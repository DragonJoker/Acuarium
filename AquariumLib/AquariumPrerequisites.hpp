#pragma once

#include <algorithm>
#include <clocale>
#include <cstdint>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <regex>
#include <string>
#include <sstream>
#include <thread>
#include <vector>

namespace aquarium
{
	typedef enum Gender : uint16_t
	{
		Female,
		Male,
		GenderCount,
	} Gender;

	typedef enum FishRace : uint16_t
	{
		Basse,
		Tuna,
		Clown,
		Sole,
		Bass,
		Carp,
		RaceCount,
	} FishRace;

	typedef enum ConsumerType : uint16_t
	{
		Carnivore,
		Herbivore,
		ConsumerTypeCount,
	} ConsumerType;

	template< FishRace RaceT > struct ConsumerTypeGetter;

	template<> struct ConsumerTypeGetter< Basse >
	{
		static ConsumerType const value = Carnivore;
	};

	template<> struct ConsumerTypeGetter< Tuna >
	{
		static ConsumerType const value = Carnivore;
	};

	template<> struct ConsumerTypeGetter< Clown >
	{
		static ConsumerType const value = Carnivore;
	};

	template<> struct ConsumerTypeGetter< Sole >
	{
		static ConsumerType const value = Herbivore;
	};

	template<> struct ConsumerTypeGetter< Bass >
	{
		static ConsumerType const value = Herbivore;
	};

	template<> struct ConsumerTypeGetter< Carp >
	{
		static ConsumerType const value = Herbivore;
	};

	template< FishRace RaceT > struct IsAgingHermaphrodite : public std::false_type{};
	template<> struct IsAgingHermaphrodite< Bass > : public std::true_type{};
	template<> struct IsAgingHermaphrodite< Basse > : public std::true_type{};

	template< FishRace RaceT > struct IsOpportunisiticHermaphrodite : public std::false_type{};
	template<> struct IsOpportunisiticHermaphrodite< Sole > : public std::true_type{};
	template<> struct IsOpportunisiticHermaphrodite< Clown > : public std::true_type{};

	class Living;
	class Seaweed;
	class RaceBase;
	class Fish;
	template< FishRace RaceT >
	class Race;
	class Aquarium;
	class AquariumGame;

	using FishPtr = std::unique_ptr< Fish >;
	using SeaweedPtr = std::unique_ptr< Seaweed >;
	using RacePtr = std::shared_ptr< RaceBase const >;
	using FishArray = std::vector< Fish >;
	using SeaweedArray = std::vector< Seaweed >;

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
		WrongMateException( Fish const & mate )
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
		Fish const & m_mate;
	};

	class NonCopyable
	{
		NonCopyable( NonCopyable const & ) = delete;
		NonCopyable & operator=( NonCopyable const & ) = delete;
		NonCopyable( NonCopyable && ) = delete;
		NonCopyable & operator=( NonCopyable && ) = delete;

	public:
		NonCopyable() = default;
		~NonCopyable() = default;
	};

	Gender getGender( std::string const & name );
	FishRace getRace( std::string const & name );
	std::string getRandomName();

	template< typename T >
	T getRandom( T const & min, T const & max )
	{
		static std::random_device device;
		static std::default_random_engine engine{ device() };

		return std::uniform_int_distribution< T >{ min, T( max - 1 ) }( engine );
	}
}
