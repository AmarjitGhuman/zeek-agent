#pragma once

#include <zeek/iaudispconsumer.h>
#include <zeek/ivirtualtable.h>
#include <zeek/izeekconfiguration.h>
#include <zeek/izeeklogger.h>

namespace zeek {
/// \brief Provides the process_events table
class ProcessEventsTablePlugin final : public IVirtualTable {
  struct PrivateData;
  std::unique_ptr<PrivateData> d;

public:
  /// \brief Factory method
  /// \param obj Where the created object is stored
  /// \param configuration An initialized configuration object
  /// \param logger An initialized logger object
  /// \return A Status object
  static Status create(Ref &obj, IZeekConfiguration &configuration,
                       IZeekLogger &logger);

  /// \brief Destructor
  virtual ~ProcessEventsTablePlugin() override;

  /// \return The table name
  virtual const std::string &name() const override;

  /// \return The table schema
  virtual const Schema &schema() const override;

  /// \brief Generates the row list containing the fields from the given
  ///        configuration object
  /// \param row_list Where the generated rows are stored
  /// \return A Status object
  virtual Status generateRowList(RowList &row_list) override;

  /// \brief Processes the specified event list, generating new rows
  /// \param event_list A list of Audit events
  /// \return A Status object
  Status processEvents(const IAudispConsumer::AuditEventList &event_list);

  /// \brief Generates a single row from the given Audit event
  /// \param row Where the generated row is stored
  /// \param audit_event a single Audit event
  /// \return A Status object
  static Status generateRow(Row &row,
                            const IAudispConsumer::AuditEvent &audit_event);

protected:
  /// \brief Constructor
  /// \param configuration An initialized configuration object
  /// \param logger An initialized logger object
  ProcessEventsTablePlugin(IZeekConfiguration &configuration,
                           IZeekLogger &logger);
};
} // namespace zeek
