/**
 *    Copyright (C) 2015 MongoDB Inc.
 *
 *    This program is free software: you can redistribute it and/or  modify
 *    it under the terms of the GNU Affero General Public License, version 3,
 *    as published by the Free Software Foundation.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Affero General Public License for more details.
 *
 *    You should have received a copy of the GNU Affero General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *    As a special exception, the copyright holders give permission to link the
 *    code of portions of this program with the OpenSSL library under certain
 *    conditions as described in each individual source file and distribute
 *    linked combinations including the program with the OpenSSL library. You
 *    must comply with the GNU Affero General Public License in all respects for
 *    all of the code used other than as permitted herein. If you modify file(s)
 *    with this exception, you may extend this exception to your version of the
 *    file(s), but you are not obligated to do so. If you do not wish to do so,
 *    delete this exception statement from your version. If you delete this
 *    exception statement from all source files in the program, then also delete
 *    it in the license file.
 */

#pragma once

#include <boost/optional.hpp>
#include <string>

#include "mongo/base/status.h"
#include "mongo/base/status_with.h"
#include "mongo/db/clientcursor.h"
#include "mongo/db/namespace_string.h"

namespace mongo {

    struct GetMoreRequest {
        /**
         * Construct an empty request.
         */
        GetMoreRequest();

        /**
         * Construct a GetMoreRequesst from the command specification and db name.
         */
        static StatusWith<GetMoreRequest> parseFromBSON(const std::string& dbname,
                                                        const BSONObj& cmdObj);

        static std::string parseNs(const std::string& dbname, const BSONObj& cmdObj);

        const NamespaceString nss;
        const CursorId cursorid;

        // The batch size is optional. If not provided, we will put as many documents into the batch
        // as fit within the byte limit.
        const boost::optional<int> batchSize;

    private:
        /**
         * Construct from parsed BSON
         */
        GetMoreRequest(const std::string& fullns, CursorId id, boost::optional<int> batch);

        /**
         * Returns a non-OK status if there are semantic errors in the parsed request
         * (e.g. a negative batchSize).
         */
        Status isValid() const;
    };

} // namespace mongo
