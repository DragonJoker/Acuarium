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

	template< FishRace Race > struct IsCarnivore : public std::false_type{};
	template<> struct IsCarnivore< Basse > : public std::true_type{};
	template<> struct IsCarnivore< Tuna > : public std::true_type{};
	template<> struct IsCarnivore< Clown > : public std::true_type{};

	template< FishRace Race > struct IsHerbivore : public std::false_type{};
	template<> struct IsHerbivore< Sole > : public std::true_type{};
	template<> struct IsHerbivore< Bass > : public std::true_type{};
	template<> struct IsHerbivore< Carp > : public std::true_type{};

	template< FishRace Race > struct IsAgingHermaphrodite : public std::false_type{};
	template<> struct IsAgingHermaphrodite< Bass > : public std::true_type{};
	template<> struct IsAgingHermaphrodite< Basse > : public std::true_type{};

	template< FishRace Race > struct IsOpportunisiticHermaphrodite : public std::false_type{};
	template<> struct IsOpportunisiticHermaphrodite< Sole > : public std::true_type{};
	template<> struct IsOpportunisiticHermaphrodite< Clown > : public std::true_type{};

	class Living;
	class Seaweed;
	class Fish;
	template< FishRace Race >
	class RacedFish;
	class Aquarium;

	using FishPtr = std::shared_ptr< Fish >;
	using SeaweedPtr = std::shared_ptr< Seaweed >;
	using FishCreator = std::function< FishPtr( uint16_t, std::string const &, Gender ) >;
	using FishArray = std::vector< FishPtr >;
	using SeaweedArray = std::vector< SeaweedPtr >;

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
		WrongMateException( FishPtr mate )
			: m_mate{ mate }
		{
		}

		virtual char const * what() const noexcept
		{
			return "Mate was not compatible";
		}

		inline FishPtr getMate()
		{
			return m_mate;
		}

	private:
		FishPtr m_mate;
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
	std::string getRandomName( std::default_random_engine & engine );

	struct NameManip
	{
		NameManip( std::string const & str );

		std::string const & m_str;
	};

	struct GenderManip
	{
		GenderManip( Gender gender );

		std::string const m_str;
	};

	struct RaceManip
	{
		RaceManip( FishRace race );

		std::string const m_str;
	};

	template< typename T >
	struct ManipCreator;

	template<>
	struct ManipCreator< std::string >
	{
		using type = NameManip;
	};

	template<>
	struct ManipCreator< Gender >
	{
		using type = GenderManip;
	};

	template<>
	struct ManipCreator< FishRace >
	{
		using type = RaceManip;
	};

	template< typename T >
	typename ManipCreator< T >::type manip( T const & value )
	{
		return typename ManipCreator< T >::type{ value };
	}

	std::ostream & operator<<( std::ostream & stream, NameManip const & manip );
	std::ostream & operator<<( std::ostream & stream, GenderManip const & manip );
	std::ostream & operator<<( std::ostream & stream, RaceManip const & manip );
}
