#ifndef RoombaAI_HPP
#define RoombaAI_HPP

//----------------------------------------------------------------
// Main code for the logic of the Roomba.
//
// Here is everything that ties it together.
//----------------------------------------------------------------

#include "Vec2.hpp"
#include "RoombaProperties.hpp"
#include "RoombaHardware.hpp"
#include "SetupPins.hpp"
#include "LinkedList.hpp"

namespace RoombaAI
{
    class RoombaChunk;
    class Roomba;

    //----------------------------------------------------------------
    // The Class of the grid with all the chunks inside.
    //
    // Every chunk will be stored in this "vector" (list)
    //----------------------------------------------------------------
    class RoombaGrid
    {
        public:
            void UpdateGrid( Roomba* roomba );

            // Get the amount of RoombaChunks stored.
            unsigned int GetAmountOfChunks();

            // Get a random chunk at this index. 
            // This might change on the next Update, so don't expect this to be the same every time.
            RoombaChunk* GetAnyChunkAt( const unsigned short& index );

            /**
             * @brief Get the chunk at the specified (grid) position.
             * 
             * @param posX Position of the Chunk on X-Axis
             * @param posY Position of the Chunk on Y-Axis
             * @param foundRoombaChunk Will return the found chunk if found. Else it will not touch the variable at all.
             * @return If a chunk is found true will be returned else false.
             */
            bool GetChunkAt( const short& posX, const short& posY, RoombaChunk* foundRoombaChunk );

            /**
             * @brief See if a chunk is on the specified (grid) position.
             * 
             * @param gridPos The position on the grid.
             * @return If a chunk is found.
             */
            bool GetChunkAt( Vec2 gridPos );

            /**
             * @brief Get the chunk at the specified (grid) position.
             * 
             * @param gridPos The position on the grid.
             * @param rc Will return the found chunk if found. Else it will not touch the variable at all.
             * @return If a chunk is found.
             */
            bool GetChunkAt( Vec2 gridPos, RoombaChunk* rc );

            /**
             * @brief Get the chunk at the specified (real world) position.
             * 
             * @param pos The position of the roomba.
             * @param gridSize The size of each chunk.
             * @param foundRoombaChunk Will return the found chunk if found. Else it will not touch the variable at all.
             * @return If a chunk is found.
             */
            bool GetChunkAt( Vec2 pos, float gridSize, RoombaChunk& foundRoombaChunk );

            // Get the chunk that was recently created.
            RoombaChunk* GetNewestChunk();

        private:
            // The list of every chunk in the grid. Will resize automatically.
            //
            // ToDo: 
            //  We should probably sort this every time or make sure to add new chunks
            //  in a sorted manner to speed up grid access.
            LinkedList<RoombaChunk> grid;

            // The newest chunk that was created.
            RoombaChunk* newestChunk;

            /**
             * @brief 
             * Add a new chunk if it doesn't exist.
             * 
             * @param posX The X-Axis position on the grid (Int)
             * @param posY The Y-Axis position on the grid (Int)
             * @return If a chunk has been created or not. (It didn't exist before (true) / It already exists (false))
             */
            bool AddIfNotExists( const short& posX, const short& posY );

            /**
             * @brief Add a new chunk, if it doesn't exist.
             * 
             * @param posX The X-Axis position on the grid (Int)
             * @param posY The Y-Axis position on the grid (Int)
             * @param newRC The new chunk that has been created. (The passed in chunk will be filled, if return = true)
             * @return If a chunk has been created or not. (It didn't exist before (true) / It already exists (false))
             */
            bool AddIfNotExists( const short& posX, const short& posY, RoombaChunk* newRC );
    };

    //----------------------------------------------------------------
    // The class of a chunk.
    //
    // Here is the data for each chunk.
    //----------------------------------------------------------------
    class RoombaChunk
    {
        public:
            // The X-Axis position on the grid.
            short posX;
            // The Y-Axis position on the grid.
            short posY;

            bool isObstacle = false;

            /**
             * @brief Construct a new Roomba Chunk object
             * 
             * @param posX The position X-Axis on the grid
             * @param posY The position Y-Axis on the grid
             */
            RoombaChunk( const short& posX, const short& posY );
    };

    class Roomba
    {
        public:

            Roomba( RoombaHardware hardware );

            /**
            * @brief 
            * Each time the Roomba moves, this should be called.
            * This updates the internal position of the Roomba 
            * and everything else dependent on it. (Like the grid)
            *
            * @param deltaDistance The distance we went from last time this function was called.
            */
            void UpdatePosition( float deltaDistance );

            // Setter for gridSize.
            void SetGridSize( float gridSize );

            // Getter for gridSize.
            float GetGridSize();

            int GetAmountOfChunks();

            // Getter for the internal position of the Roomba.
            Vec2 GetPosition();

            // Get the direction the roomba is looking towards.
            RoombaDirection GetLookingDirection();

            // Set the direction the roomba is looking towards.
            void SetLookingDirection( RoombaDirection rd );

            RoombaChunk* GetAnyChunkAt( const short& i );

            // void EXPERIMENTAL_DeleteGrid()
            // {
            //     delete gridPtr;
            //     gridPtr = new RoombaGrid();
            // }

        private:
            // The internal position of the roomba.
            Vec2 roombaPosition = Vec2( 0, 0 );

            // The position of the roomba in grid coordinates
            Vec2 gridRoombaPosition = Vec2( 0, 0 );

            /* The direction the roomba is looking towards.
            (Nodirection direction will be ignored!) */
            RoombaDirection lookingDirection = RoombaDirection::NODIRECTION;

            // The size of each "chunk" (square) on the grid.
            float gridSize;
        
            // The whole grid with all of the chunks inside
            RoombaGrid grid;
            // RoombaGrid* gridPtr;

            // The last chunk, that was accessed.
            RoombaChunk* lastAccessedChunk = nullptr;

            // The distance we went from last time the UpdatePosition function was called.
            float deltaDistance;

            // The position of the Roomba inside the current chunk [0; 1)
            // lazy, because it is not completely exact.
            float currentLazyChunkPos;

            RoombaHardware hardware;

            // Update the current chunks and last chunks WallState. 
            void UpdateChunkWallInfo();

            // Set the WallState at the current chunk.
            void SetWallOnChunk( RoombaChunk& rc, const bool& set, RoombaDirection& rd );

            // The main AI system of the movement logic of the roomba.
            void MoveRoomba();

            // If the roomba detects something at the front, it'll turn right.
            // Used as part of the roomba logic or if the AI fails to turn right.
            void SimpleMove();

            // Scan for chunks that haven't been done yet.
            void ScanForUnfoundChunks();
    };
}

#endif