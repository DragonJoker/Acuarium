#pragma once

#include "Aquarium.hpp"

namespace aquarium
{
	struct TurnAdds
	{
		FishArray m_fishes;
		SeaweedArray m_seaweeds;
	};

	using TurnAddsMap = std::map< uint32_t, TurnAdds >;

	class AquariumGame
	{
	public:
		AquariumGame( Aquarium & aquarium, TurnAddsMap && turnsAdds );
		void update();

		inline uint32_t getTurn()const
		{
			return m_turn;
		}

	private:
		void doAddTurnAdds();
		void doGrowLivings( FishArray & fishes, SeaweedArray & seaweeds, FishArray & newFishes, SeaweedArray & newSeaweeds );
		void doUpdateLivings( FishArray & fishes, SeaweedArray & seaweeds, FishArray & newFishes, SeaweedArray & newSeaweeds );

	private:
		Aquarium & m_aquarium;
		TurnAddsMap m_turnsAdds;
		uint32_t m_turn{ 0 };
	};
}
