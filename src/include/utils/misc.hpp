#pragma once

#include <duckdb.hpp>
#include "utils/compatibility.hpp"
#include <utility>

namespace duckdb {

enum class TestDrivenTransactionState { NONE, STARTED, TO_COMMIT, TO_ROLLBACK };

void UpdateTxStateFromTxType(const TransactionType type, TestDrivenTransactionState &state);
void UpdateTxStateAfterStatement(Connection &con, TestDrivenTransactionState &state, bool rollback_if_none = false);

void DetachAllDatabases(ClientContext &);
void UseDBAndDetachOthers(Connection &, const std::string &, bool);

std::string UUIDToString(const hugeint_t &);

// Runs a query (SQL string or statement) with a fully materialized result.
// DuckDB 2.1 replaced the `allow_stream_result` flag with `QueryParameters`, whose default materializes.
template <class QUERY>
unique_ptr<QueryResult> MaterializedQuery(ClientContext &context, QUERY &&query) {
#if DUCKDB_VERSION_BEFORE(2, 1, 0)
	return context.Query(std::forward<QUERY>(query), false);
#else
	return context.Query(std::forward<QUERY>(query), QueryParameters());
#endif
}

} // namespace duckdb
