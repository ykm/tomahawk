/* === This file is part of Tomahawk Player - <http://tomahawk-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *
 *   Tomahawk is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Tomahawk is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DATABASECOMMAND_ALLTRACKS_H
#define DATABASECOMMAND_ALLTRACKS_H

#include <QObject>
#include <QVariantMap>

#include "databasecommand.h"
#include "collection.h"
#include "typedefs.h"
#include "query.h"

#include "dllmacro.h"

class DLLEXPORT DatabaseCommand_AllTracks : public DatabaseCommand
{
Q_OBJECT
public:
    enum SortOrder {
        None = 0,
        Album = 1,
        ModificationTime = 2,
        AlbumPosition = 3
    };

    explicit DatabaseCommand_AllTracks( const Tomahawk::collection_ptr& collection = Tomahawk::collection_ptr(), QObject* parent = 0 )
        : DatabaseCommand( parent )
        , m_collection( collection )
        , m_artist( 0 )
        , m_album( 0 )
        , m_amount( 0 )
        , m_sortOrder( DatabaseCommand_AllTracks::None )
        , m_sortDescending( false )
    {}

    virtual void exec( DatabaseImpl* );

    virtual bool doesMutates() const { return false; }
    virtual QString commandname() const { return "alltracks"; }

    void setArtist( Tomahawk::Artist* artist ) { m_artist = artist; }
    void setAlbum( Tomahawk::Album* album ) { m_album = album; }

    void setLimit( unsigned int amount ) { m_amount = amount; }
    void setSortOrder( DatabaseCommand_AllTracks::SortOrder order ) { m_sortOrder = order; }
    void setSortDescending( bool descending ) { m_sortDescending = descending; }

signals:
    void tracks( const QList<Tomahawk::query_ptr>&, const QVariant& data );
    void done( const Tomahawk::collection_ptr& );

private:
    Tomahawk::collection_ptr m_collection;

    Tomahawk::Artist* m_artist;
    Tomahawk::Album* m_album;

    unsigned int m_amount;
    DatabaseCommand_AllTracks::SortOrder m_sortOrder;
    bool m_sortDescending;
};

#endif // DATABASECOMMAND_ALLTRACKS_H
