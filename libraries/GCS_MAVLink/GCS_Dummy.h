#include "GCS.h"

const AP_FWVersion fwver
{
    major: 3,
    minor: 1,
    patch: 4,
    fw_type: FIRMWARE_VERSION_TYPE_DEV,
    fw_string: "Dummy GCS"
};

/*
 *  GCS backend used for many examples and tools
 */
class GCS_MAVLINK_Dummy : public GCS_MAVLINK
{
    void data_stream_send(void) override {}
    uint32_t telem_delay() const override { return 0; }
    void handleMessage(mavlink_message_t * msg) override {}
    bool try_send_message(enum ap_message id) { return true; }
    bool handle_guided_request(AP_Mission::Mission_Command &cmd) override { return true; }
    void handle_change_alt_request(AP_Mission::Mission_Command &cmd) override {}

protected:

    Compass *get_compass() const override { return nullptr; };
    AP_Mission *get_mission() override { return nullptr; }
    AP_Rally *get_rally() const override { return nullptr; };
    AP_GPS *get_gps() const override { return nullptr; };
    AP_Camera *get_camera() const override { return nullptr; };
    AP_ServoRelayEvents *get_servorelayevents() const override { return nullptr; }
    const AP_FWVersion &get_fwver() const override { return fwver; }

    uint8_t sysid_my_gcs() const override { return 1; }
    bool set_mode(uint8_t mode) override { return false; };

};

/*
 * a GCS singleton used for many example sketches and tools
 */

extern const AP_HAL::HAL& hal;

class GCS_Dummy : public GCS
{
    GCS_MAVLINK_Dummy dummy_backend;
    uint8_t num_gcs() const override { return 1; }
    GCS_MAVLINK_Dummy &chan(const uint8_t ofs) override { return dummy_backend; }
    const GCS_MAVLINK_Dummy &chan(const uint8_t ofs) const override { return dummy_backend; };

    void send_statustext(MAV_SEVERITY severity, uint8_t dest_bitmask, const char *text) { hal.console->printf("TOGCS: %s\n", text); }
};
