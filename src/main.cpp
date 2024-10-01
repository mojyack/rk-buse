#include "buse/block-operator.hpp"
#include "buse/buse.hpp"
#include "macros/assert.hpp"
#include "xrock/rock.h"

struct EDLOperator : buse::BlockOperator {
    xrock_ctx_t* ctx;

    auto read_block(const size_t block, const size_t blocks, void* buf) -> bool override {
        ensure(rock_flash_read_lba(ctx, block, blocks, buf) == 1);
        return true;
    }

    auto write_block(size_t block, size_t blocks, const void* buf) -> bool override {
        ensure(rock_flash_write_lba(ctx, block, blocks, (void*)buf) == 1);
        return true;
    }
};

auto main(const int /*argc*/, const char* const* /*argv*/) -> int {
    auto ctx = xrock_ctx_t();
    ensure(libusb_init(&ctx.context) == 0);
    ensure(xrock_init(&ctx));
    auto flash_info = flash_info_t();
    ensure(rock_flash_detect(&ctx, &flash_info));
    print("detected ", flash_info.sector_total, " sectors(", flash_info.sector_total * 512 / 1024 / 1024, "MB)");

    auto op        = EDLOperator{};
    op.ctx         = &ctx;
    op.block_size  = 512;
    op.block_count = flash_info.sector_total;
    return buse::run("/dev/nbd0", op);
}
