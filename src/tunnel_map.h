/* $Id$ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file tunnel_map.h Map accessors for tunnels. */

#ifndef TUNNEL_MAP_H
#define TUNNEL_MAP_H

#include "road_map.h"


/**
 * Is this a tunnel (entrance)?
 * @param t the tile that might be a tunnel
 * @pre IsTunnelBridgeTile(t)
 * @return true if and only if this tile is a tunnel (entrance)
 */
static inline bool IsTunnel(TileIndex t)
{
	assert(IsTunnelBridgeTile(t));
	return !HasBit(_mc[t].m5, 7);
}

/**
 * Is this a tunnel (entrance)?
 * @param t the tile that might be a tunnel
 * @return true if and only if this tile is a tunnel (entrance)
 */
static inline bool IsTunnelTile(TileIndex t)
{
	return IsTunnelBridgeTile(t) && IsTunnel(t);
}

/**
 * Get the transport type of the tunnel (road or rail)
 * @param t The tile to analyze
 * @pre IsTunnelTile(t)
 * @return the transport type in the tunnel
 */
static inline TransportType GetTunnelTransportType(TileIndex t)
{
	assert(IsTunnelTile(t));
	return (TransportType)GB(_mc[t].m5, 6, 2);
}

TileIndex GetOtherTunnelEnd(TileIndex);
bool IsTunnelInWay(TileIndex, int z);
bool IsTunnelInWayDir(TileIndex tile, int z, DiagDirection dir);

/**
 * Makes a road tunnel entrance
 * @param t the entrance of the tunnel
 * @param o the owner of the entrance
 * @param d the direction facing out of the tunnel
 * @param r the road type used in the tunnel
 */
static inline void MakeRoadTunnel(TileIndex t, Owner o, DiagDirection d, RoadTypes r)
{
	SetTileType(t, TT_TUNNELBRIDGE_TEMP);
	SetTileOwner(t, o);
	_mc[t].m2 = 0;
	_mc[t].m3 = 0;
	_mc[t].m4 = 0;
	_mc[t].m5 = (TRANSPORT_ROAD << 6) | d;
	SB(_mc[t].m0, 2, 2, 0);
	_mc[t].m7 = 0;
	SetRoadOwner(t, ROADTYPE_ROAD, o);
	if (o != OWNER_TOWN) SetRoadOwner(t, ROADTYPE_TRAM, o);
	SetRoadTypes(t, r);
}

/**
 * Makes a rail tunnel entrance
 * @param t the entrance of the tunnel
 * @param o the owner of the entrance
 * @param d the direction facing out of the tunnel
 * @param r the rail type used in the tunnel
 */
static inline void MakeRailTunnel(TileIndex t, Owner o, DiagDirection d, RailType r)
{
	SetTileType(t, TT_TUNNELBRIDGE_TEMP);
	SetTileOwner(t, o);
	_mc[t].m2 = 0;
	_mc[t].m3 = r;
	_mc[t].m4 = 0;
	_mc[t].m5 = (TRANSPORT_RAIL << 6) | d;
	SB(_mc[t].m0, 2, 2, 0);
	_mc[t].m7 = 0;
}

#endif /* TUNNEL_MAP_H */
