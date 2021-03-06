#include <gtest/gtest.h>

#include "../src/sha3.hpp"

TEST(SHA3Test, SingleRoundTest) {
    // https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHA3-512_Msg0.pdf
    std::array<uint64_t, 25> init_state = {
        0x0000000000000006,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x8000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
    };
    std::array<uint64_t, 25> after_theta_round0 = {
        0x0000000000000006,
        0x0000000000000006,
        0x0000000000000001,
        0x0000000000000000,
        0x800000000000000c,
        0x0000000000000000,
        0x0000000000000006,
        0x0000000000000001,
        0x8000000000000000,
        0x800000000000000c,
        0x0000000000000000,
        0x0000000000000006,
        0x0000000000000001,
        0x0000000000000000,
        0x800000000000000c,
        0x0000000000000000,
        0x0000000000000006,
        0x0000000000000001,
        0x0000000000000000,
        0x800000000000000c,
        0x0000000000000000,
        0x0000000000000006,
        0x0000000000000001,
        0x0000000000000000,
        0x800000000000000c,
    };
    std::array<uint64_t, 25> after_chi_round0 = {
        0x0000080000000006,
        0x0000600000000000,
        0x0000080000032000,
        0x0000000000000006,
        0x0000600000032000,
        0x0000000000000000,
        0x0000c00000c80000,
        0x2000000000000000,
        0x0000c00000000000,
        0x2000000000c80000,
        0x000000000000000c,
        0x0000000000000cc0,
        0x0000000000000000,
        0x0000000000000c8c,
        0x0000000000000040,
        0x0000000064001800,
        0x0000000000008000,
        0x0000000000001800,
        0x0000000064008000,
        0x0000000000000000,
        0x4000064000000000,
        0x0040000000000000,
        0x0000064000000018,
        0x4000000000000000,
        0x0040000000000018,
    };
    std::array<uint64_t, 25> after_iota_round0 = {
        0x0000080000000007,
        0x0000600000000000,
        0x0000080000032000,
        0x0000000000000006,
        0x0000600000032000,
        0x0000000000000000,
        0x0000c00000c80000,
        0x2000000000000000,
        0x0000c00000000000,
        0x2000000000c80000,
        0x000000000000000c,
        0x0000000000000cc0,
        0x0000000000000000,
        0x0000000000000c8c,
        0x0000000000000040,
        0x0000000064001800,
        0x0000000000008000,
        0x0000000000001800,
        0x0000000064008000,
        0x0000000000000000,
        0x4000064000000000,
        0x0040000000000000,
        0x0000064000000018,
        0x4000000000000000,
        0x0040000000000018,
    };
    std::array<uint64_t, 25> after_theta_round1 = {
        0x20c12800015a39df,
        0x000072c06406683b,
        0x80412800c8cab5d4,
        0x6080ce40019578ae,
        0xc000bc80ac039c9c,
        0x20c12000015a39d8,
        0x0000d2c064ce683b,
        0xa0412000c8c995d4,
        0x60800e40019578a8,
        0xe000dc80acc8bc9c,
        0x20c12000015a39d4,
        0x000012c0640664fb,
        0x80412000c8c995d4,
        0x6080ce4001957424,
        0xc000dc80ac00bcdc,
        0x20c12000655a21d8,
        0x000012c06406e83b,
        0x80412000c8c98dd4,
        0x6080ce406595f8a8,
        0xc000dc80ac00bc9c,
        0x60c12640015a39d8,
        0x004012c06406683b,
        0x80412640c8c995cc,
        0x2080ce40019578a8,
        0xc040dc80ac00bc84,
    };
    std::array<uint64_t, 25> after_chi_round1 = {
        0x28ed2c02015a39dd,
        0x6683a2bd19201655,
        0x7b8ead0223212646,
        0xc8cdb2bf155619d6,
        0xf122bb0023053610,
        0x0618578ae419c244,
        0x110cac8bc9c6000d,
        0x060104c813d0fc98,
        0xdd163302e45800c4,
        0x580aacc910df32b0,
        0x8003cf48808cd0e2,
        0x109480363259e968,
        0x19032fa8af800298,
        0x00dc602c08b0ccb2,
        0x8948055ad500a60c,
        0x05281cf4f781e9e4,
        0x85a3f9e6ca7a0020,
        0x286b811a19927958,
        0x9540784460ea40a4,
        0xb8a301cc48139578,
        0x205e6460325cad37,
        0xe031d006a200ca34,
        0x015e25601077e072,
        0x9453b041a0620ddb,
        0x55204b069019e264,
    };
    std::array<uint64_t, 25> after_iota_round1 = {
        0x28ed2c02015ab95f,
        0x6683a2bd19201655,
        0x7b8ead0223212646,
        0xc8cdb2bf155619d6,
        0xf122bb0023053610,
        0x0618578ae419c244,
        0x110cac8bc9c6000d,
        0x060104c813d0fc98,
        0xdd163302e45800c4,
        0x580aacc910df32b0,
        0x8003cf48808cd0e2,
        0x109480363259e968,
        0x19032fa8af800298,
        0x00dc602c08b0ccb2,
        0x8948055ad500a60c,
        0x05281cf4f781e9e4,
        0x85a3f9e6ca7a0020,
        0x286b811a19927958,
        0x9540784460ea40a4,
        0xb8a301cc48139578,
        0x205e6460325cad37,
        0xe031d006a200ca34,
        0x015e25601077e072,
        0x9453b041a0620ddb,
        0x55204b069019e264,
    };

    SHA3_512 sha3;
    sha3.state = init_state;
    EXPECT_EQ(sha3.state, init_state);

    sha3.theta();
    EXPECT_EQ(sha3.state, after_theta_round0);
    const auto b = sha3.rho_pi();
    sha3.chi(b);
    EXPECT_EQ(sha3.state, after_chi_round0);
    sha3.iota(0);
    EXPECT_EQ(sha3.state, after_iota_round0);

    sha3.theta();
    EXPECT_EQ(sha3.state, after_theta_round1);
    const auto b_round1 = sha3.rho_pi();
    sha3.chi(b_round1);
    EXPECT_EQ(sha3.state, after_chi_round1);
    sha3.iota(1);
    EXPECT_EQ(sha3.state, after_iota_round1);
}

TEST(SHA3Test, AbsorbSqueezeTest) {
    SHA3_512::Block to_absorb = {
        0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80
    };
    std::array<uint64_t, 25> init_state = {
        0x0000000000000006,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x8000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
    };

    SHA3_512 sha3;
    sha3.absorb(to_absorb);
    EXPECT_EQ(sha3.state, init_state);
    EXPECT_EQ(sha3.squeeze(), to_absorb);
}

TEST(SHA3Test, FullRunIteration) {
    SHA3_512::Block to_absorb = {
        0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80
    };

    std::array<uint64_t, 25> final_state = {
        0xc59a3aa2cc739fa6,
        0x6e755a18dc67b5c8,
        0x5958e24f1682c997,
        0xa6805c47c1dcd1e0,
        0x4cf9f5f13a12b215,
        0x58c53a2c40e9e311,
        0xe3d3b6959d1900f5,
        0x26cd1d2886857501,
        0xb8538fe7b8c54b36,
        0x00ad9fdef4a7dd23,
        0x0cea9f9f2fb77de6,
        0xc5ad765af1fec9e3,
        0x65fb8711fd2eeb85,
        0xe367513173a2c9f9,
        0x07d422a3b668fa14,
        0x888ceccd2a505d01,
        0x0946d0ce84774f5c,
        0x564b48964a1535bb,
        0xcd7a60887c41d325,
        0x9edf5eae9bc9c2e4,
        0x1826a255fbd02aea,
        0x2b3e436049d2119e,
        0x76970973a445e00e,
        0x19a89bdb39e75ddd,
        0xeed7a5a703b94cd5,
    };

    SHA3_512 sha3;
    sha3.absorb(to_absorb);
    sha3.f();
    EXPECT_EQ(sha3.state, final_state);
}

TEST(SHA3Test, FullRunHash) {
    SHA3_512::Digest hash_val = {
        0xA6, 0x9F, 0x73, 0xCC, 0xA2, 0x3A, 0x9A, 0xC5, 0xC8, 0xB5, 0x67, 0xDC, 0x18, 0x5A, 0x75, 0x6E,
        0x97, 0xC9, 0x82, 0x16, 0x4F, 0xE2, 0x58, 0x59, 0xE0, 0xD1, 0xDC, 0xC1, 0x47, 0x5C, 0x80, 0xA6,
        0x15, 0xB2, 0x12, 0x3A, 0xF1, 0xF5, 0xF9, 0x4C, 0x11, 0xE3, 0xE9, 0x40, 0x2C, 0x3A, 0xC5, 0x58,
        0xF5, 0x00, 0x19, 0x9D, 0x95, 0xB6, 0xD3, 0xE3, 0x01, 0x75, 0x85, 0x86, 0x28, 0x1D, 0xCD, 0x26
    };

    SHA3_512 sha3;
    const std::string msg = "";
    EXPECT_EQ(sha3.hash(std::begin(msg), std::end(msg)).digest(), hash_val);
}
TEST(SHA3Test, FullRunHashHex) {
    std::string hash_val = "a69f73cca23a9ac5c8b567dc185a756e97c982164fe25859e0d1dcc1475c80a615b2123af1f5f94c11e3e9402c3ac558f500199d95b6d3e301758586281dcd26";

    SHA3_512 sha3;
    const std::string msg = "";
    EXPECT_EQ(sha3.hash(std::begin(msg), std::end(msg)).hexdigest(), hash_val);
}
