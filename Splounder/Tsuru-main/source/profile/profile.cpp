#include "game/profile/profile.h"
#include "game/actor/actor.h"

REGISTER_PROFILE(Actor, ProfileID::NullActor);

Profile* Profile::profilesCustom[Profile::NUM_PROFILES_CUSTOM];
s16 Profile::prioritiesCustom[Profile::NUM_PROFILES_CUSTOM] = { 0 };
u8 Profile::resourcesLoadAtCustom[Profile::NUM_PROFILES_CUSTOM] = { 0 };
u8 Profile::resourceCountCustom[Profile::NUM_PROFILES_CUSTOM] = { 0 };
const sead::SafeString* Profile::resourceListsCustom[Profile::NUM_PROFILES_CUSTOM] = { nullptr };

Profile::Profile(Actor* (*buildFunc)(const ActorBuildInfo*), u32 id, const sead::SafeString& name, const ActorInfo* actorInfo, u32 flags) {
    this->buildFunc = buildFunc;
    this->id = id;

    if (actorInfo)
        this->actorInfo = actorInfo;
    else
        this->actorInfo = &ActorInfo::sDefault;

    this->hasResourcesLoaded = 0;
    this->flags = flags;

    if (id < NUM_PROFILES_ORIGINAL)
        profilesOriginal[id] = this;

    else if (id < NUM_PROFILES)
        profilesCustom[id - NUM_PROFILES_ORIGINAL] = this;

    else
        profilesOriginal[0] = this;
}

Profile* Profile::get(u32 id) {
    if (id < NUM_PROFILES_ORIGINAL)
        return profilesOriginal[id];

    if (id < NUM_PROFILES)
        return profilesCustom[id - NUM_PROFILES_ORIGINAL];

    return profilesOriginal[0];
}

s16 Profile::getPriority(u32 id) {
    if (id < NUM_PROFILES_ORIGINAL)
        return prioritiesOriginal[id];

    if (id < NUM_PROFILES)
        return prioritiesCustom[id - NUM_PROFILES_ORIGINAL];

    return -1;
}

Profile::LoadResourcesAt::__type__ Profile::getResourcesLoadAt(u32 id) {
    if (id < NUM_PROFILES_ORIGINAL)
        return static_cast<Profile::LoadResourcesAt::__type__>(resourcesLoadAtOriginal[id]);

    if (id < NUM_PROFILES)
        return static_cast<Profile::LoadResourcesAt::__type__>(resourcesLoadAtCustom[id - NUM_PROFILES_ORIGINAL]);

    return LoadResourcesAt::Boot;
}

u8 Profile::getResourceCount(u32 id) {
    if (id < NUM_PROFILES_ORIGINAL)
        return resourceCountOriginal[id];

    if (id < NUM_PROFILES)
        return resourceCountCustom[id - NUM_PROFILES_ORIGINAL];

    return 0;
}

const sead::SafeString* Profile::getResourceList(u32 id) {
    if (id < NUM_PROFILES_ORIGINAL)
        return resourceListsOriginal[id];

    if (id < NUM_PROFILES)
        return resourceListsCustom[id - NUM_PROFILES_ORIGINAL];

    return nullptr;
}

u32 Profile::getNumProfiles() {
    return NUM_PROFILES;
}

//* Remember to add the new profile to the ProfileID enum in profileid.h and to the end of this list

u32 Profile::spriteToProfileList[] = {
    467,    //   0
    469,    //   1
    479,    //   2
    480,    //   3
    481,    //   4
    482,    //   5
    483,    //   6
    484,    //   7
    485,    //   8
    486,    //   9
    487,    //  10
    488,    //  11
    489,    //  12
    490,    //  13
    492,    //  14
    495,    //  15
    496,    //  16
    497,    //  17
    498,    //  18
    512,    //  19
    515,    //  20
    516,    //  21
    381,    //  22
    517,    //  23
    518,    //  24
    565,    //  25
    575,    //  26
    578,    //  27
    579,    //  28
    580,    //  29
    581,    //  30
    275,    //  31
    740,    //  32
    562,    //  33
    563,    //  34
    601,    //  35
    0,      //  36
    1,      //  37
    2,      //  38
    3,      //  39
    4,      //  40
    5,      //  41
    8,      //  42
    9,      //  43
    750,    //  44
    426,    //  45
    427,    //  46
    429,    //  47
    430,    //  48
    118,    //  49
    119,    //  50
    610,    //  51
    191,    //  52
    549,    //  53
    755,    //  54
    513,    //  55
    551,    //  56
    548,    //  57
    562,    //  58
    289,    //  59
    291,    //  60
    294,    //  61
    774,    //  62
    499,    //  63
    500,    //  64
    395,    //  65
    398,    //  66
    612,    //  67
    39,     //  68
    40,     //  69
    11,     //  70
    60,     //  71
    64,     //  72
    393,    //  73
    519,    //  74
    763,    //  75
    757,    //  76
    765,    //  77
    759,    //  78
    761,    //  79
    54,     //  80
    56,     //  81
    775,    //  82
    776,    //  83
    777,    //  84
    556,    //  85
    383,    //  86
    405,    //  87
    84,     //  88
    85,     //  89
    86,     //  90
    87,     //  91
    88,     //  92
    89,     //  93
    82,     //  94
    83,     //  95
    613,    //  96
    587,    //  97
    614,    //  98
    385,    //  99
    13,     // 100
    530,    // 101
    588,    // 102
    112,    // 103
    344,    // 104
    345,    // 105
    542,    // 106
    602,    // 107
    603,    // 108
    604,    // 109
    606,    // 110
    608,    // 111
    113,    // 112
    532,    // 113
    547,    // 114
    747,    // 115
    41,     // 116
    43,     // 117
    42,     // 118
    620,    // 119
    539,    // 120
    787,    // 121
    789,    // 122
    121,    // 123
    122,    // 124
    628,    // 125
    629,    // 126
    630,    // 127
    631,    // 128
    540,    // 129
    625,    // 130
    545,    // 131
    129,    // 132
    184,    // 133
    790,    // 134
    635,    // 135
    636,    // 136
    648,    // 137
    649,    // 138
    335,    // 139
    336,    // 140
    334,    // 141
    333,    // 142
    450,    // 143
    441,    // 144
    190,    // 145
    143,    // 146
    296,    // 147
    297,    // 148
    406,    // 149
    168,    // 150
    170,    // 151
    387,    // 152
    187,    // 153
    310,    // 154
    145,    // 155
    123,    // 156
    800,    // 157
    411,    // 158
    139,    // 159
    140,    // 160
    141,    // 161
    142,    // 162
    124,    // 163
    521,    // 164
    45,     // 165
    46,     // 166
    425,    // 167
    14,     // 168
    15,     // 169
    522,    // 170
    101,    // 171
    102,    // 172
    103,    // 173
    104,    // 174
    524,    // 175
    114,    // 176
    115,    // 177
    116,    // 178
    627,    // 179
    637,    // 180
    639,    // 181
    211,    // 182
    778,    // 183
    350,    // 184
    779,    // 185
    212,    // 186
    651,    // 187
    193,    // 188
    312,    // 189
    300,    // 190
    302,    // 191
    215,    // 192
    217,    // 193
    561,    // 194
    321,    // 195
    17,     // 196
    793,    // 197
    791,    // 198
    388,    // 199
    80,     // 200
    792,    // 201
    389,    // 202
    390,    // 203
    652,    // 204
    311,    // 205
    678,    // 206
    128,    // 207
    314,    // 208
    315,    // 209
    77,     // 210
    258,    // 211
    584,    // 212
    238,    // 213
    47,     // 214
    555,    // 215
    684,    // 216
    61,     // 217
    780,    // 218
    781,    // 219
    782,    // 220
    783,    // 221
    194,    // 222
    679,    // 223
    448,    // 224
    683,    // 225
    355,    // 226
    356,    // 227
    95,     // 228
    785,    // 229
    693,    // 230
    357,    // 231
    200,    // 232
    298,    // 233
    299,    // 234
    375,    // 235
    377,    // 236
    748,    // 237
    51,     // 238
    173,    // 239
    222,    // 240
    197,    // 241
    198,    // 242
    447,    // 243
    694,    // 244
    685,    // 245
    681,    // 246
    470,    // 247
    199,    // 248
    508,    // 249
    152,    // 250
    236,    // 251
    240,    // 252
    798,    // 253
    797,    // 254
    471,    // 255
    154,    // 256
    201,    // 257
    202,    // 258
    502,    // 259
    117,    // 260
    205,    // 261
    206,    // 262
    279,    // 263
    126,    // 264
    53,     // 265
    158,    // 266
    799,    // 267
    283,    // 268
    208,    // 269
    767,    // 270
    147,    // 271
    148,    // 272
    149,    // 273
    162,    // 274
    98,     // 275
    553,    // 276
    407,    // 277
    220,    // 278
    408,    // 279
    92,     // 280
    409,    // 281
    632,    // 282
    52,     // 283
    203,    // 284
    204,    // 285
    654,    // 286
    358,    // 287
    756,    // 288
    224,    // 289
    225,    // 290
    20,     // 291
    226,    // 292
    227,    // 293
    229,    // 294
    228,    // 295
    695,    // 296
    49,     // 297
    353,    // 298
    359,    // 299
    360,    // 300
    510,    // 301
    680,    // 302
    771,    // 303
    233,    // 304
    670,    // 305
    354,    // 306
    234,    // 307
    231,    // 308
    232,    // 309
    671,    // 310
    55,     // 311
    93,     // 312
    803,    // 313
    235,    // 314
    230,    // 315
    153,    // 316
    682,    // 317
    655,    // 318
    178,    // 319
    658,    // 320
    554,    // 321
    805,    // 322
    391,    // 323
    179,    // 324
    414,    // 325
    413,    // 326
    167,    // 327
    415,    // 328
    566,    // 329
    180,    // 330
    567,    // 331
    568,    // 332
    569,    // 333
    525,    // 334
    527,    // 335
    674,    // 336
    673,    // 337
    324,    // 338
    241,    // 339
    416,    // 340
    806,    // 341
    570,    // 342
    571,    // 343
    585,    // 344
    243,    // 345
    772,    // 346
    245,    // 347
    248,    // 348
    244,    // 349
    150,    // 350
    505,    // 351
    676,    // 352
    50,     // 353
    250,    // 354
    210,    // 355
    251,    // 356
    653,    // 357
    176,    // 358
    252,    // 359
    177,    // 360
    21,     // 361
    773,    // 362
    807,    // 363
    572,    // 364
    449,    // 365
    22,     // 366
    363,    // 367
    696,    // 368
    436,    // 369
    419,    // 370
    151,    // 371
    256,    // 372
    100,    // 373
    801,    // 374
    802,    // 375
    73,     // 376
    59,     // 377
    812,    // 378
    815,    // 379
    316,    // 380
    378,    // 381
    659,    // 382
    699,    // 383
    590,    // 384
    701,    // 385
    397,    // 386
    817,    // 387
    259,    // 388
    706,    // 389
    155,    // 390
    157,    // 391
    820,    // 392
    365,    // 393
    816,    // 394
    79,     // 395
    260,    // 396
    305,    // 397
    306,    // 398
    820,    // 399
    97,     // 400
    26,     // 401
    751,    // 402
    703,    // 403
    343,    // 404
    66,     // 405
    708,    // 406
    90,     // 407
    830,    // 408
    366,    // 409
    254,    // 410
    710,    // 411
    687,    // 412
    459,    // 413
    728,    // 414
    729,    // 415
    634,    // 416
    730,    // 417
    731,    // 418
    732,    // 419
    733,    // 420
    734,    // 421
    317,    // 422
    24,     // 423
    262,    // 424
    263,    // 425
    466,    // 426
    285,    // 427
    255,    // 428
    67,     // 429
    63,     // 430
    62,     // 431
    686,    // 432
    823,    // 433
    163,    // 434
    688,    // 435
    94,     // 436
    467,    // 437
    467,    // 438
    161,    // 439
    573,    // 440
    644,    // 441
    660,    // 442
    528,    // 443
    286,    // 444
    831,    // 445
    646,    // 446
    677,    // 447
    814,    // 448
    808,    // 449
    711,    // 450
    456,    // 451
    453,    // 452
    328,    // 453
    329,    // 454
    16,     // 455
    712,    // 456
    91,     // 457
    136,    // 458
    714,    // 459
    29,     // 460
    30,     // 461
    715,    // 462
    348,    // 463
    264,    // 464
    323,    // 465
    690,    // 466
    265,    // 467
    716,    // 468
    735,    // 469
    752,    // 470
    472,    // 471
    473,    // 472
    374,    // 473
    828,    // 474
    318,    // 475
    514,    // 476
    725,    // 477
    372,    // 478
    74,     // 479
    435,    // 480
    504,    // 481
    538,    // 482
    376,    // 483
    48,     // 484
    68,     // 485
    794,    // 486
    586,    // 487
    661,    // 488
    266,    // 489
    267,    // 490
    269,    // 491
    270,    // 492
    58,     // 493
    822,    // 494
    32,     // 495
    421,    // 496
    691,    // 497
    394,    // 498
    75,     // 499
    768,    // 500
    19,     // 501
    769,    // 502
    276,    // 503
    562,    // 504
    563,    // 505
    181,    // 506
    33,     // 507
    257,    // 508
    341,    // 509
    342,    // 510
    134,    // 511
    166,    // 512
    832,    // 513
    833,    // 514
    69,     // 515
    130,    // 516
    131,    // 517
    132,    // 518
    133,    // 519
    349,    // 520
    834,    // 521
    223,    // 522
    320,    // 523
    71,     // 524
    307,    // 525
    308,    // 526
    692,    // 527
    835,    // 528
    675,    // 529
    174,    // 530
    837,    // 531
    707,    // 532
    369,    // 533
    213,    // 534
    214,    // 535
    616,    // 536
    617,    // 537
    280,    // 538
    379,    // 539
    81,     // 540
    615,    // 541
    76,     // 542
    462,    // 543
    78,     // 544
    672,    // 545
    745,    // 546
    463,    // 547
    188,    // 548
    70,     // 549
    491,    // 550
    281,    // 551
    503,    // 552
    364,    // 553
    838,    // 554
    380,    // 555
    840,    // 556
    34,     // 557
    689,    // 558
    458,    // 559
    273,    // 560
    795,    // 561
    57,     // 562
    65,     // 563
    589,    // 564
    650,    // 565
    183,    // 566
    560,    // 567
    662,    // 568
    457,    // 569
    36,     // 570
    739,    // 571
    746,    // 572
    218,    // 573
    135,    // 574
    338,    // 575
    337,    // 576
    339,    // 577
    340,    // 578
    641,    // 579
    642,    // 580
    105,    // 581
    106,    // 582
    107,    // 583
    325,    // 584
    242,    // 585
    546,    // 586
    541,    // 587
    534,    // 588
    535,    // 589
    536,    // 590
    537,    // 591
    543,    // 592
    665,    // 593
    668,    // 594
    468,    // 595
    813,    // 596
    544,    // 597
    182,    // 598
    754,    // 599
    331,    // 600
    464,    // 601
    239,    // 602
    788,    // 603
    824,    // 604
    825,    // 605
    382,    // 606
    428,    // 607
    849,    // 608
    274,    // 609
    796,    // 610
    507,    // 611
    284,    // 612
    137,    // 613
    138,    // 614
    531,    // 615
    38,     // 616
    440,    // 617
    246,    // 618
    247,    // 619
    550,    // 620
    552,    // 621
    850,    // 622
    577,    // 623
    18,     // 624
    175,    // 625
    666,    // 626
    271,    // 627
    31,     // 628
    626,    // 629
    277,    // 630
    278,    // 631
    221,    // 632
    361,    // 633
    249,    // 634
    607,    // 635
    605,    // 636
    609,    // 637
    664,    // 638
    455,    // 639
    557,    // 640
    367,    // 641
    12,     // 642
    656,    // 643
    657,    // 644
    156,    // 645
    108,    // 646
    109,    // 647
    110,    // 648
    111,    // 649
    431,    // 650
    638,    // 651
    207,    // 652
    633,    // 653
    465,    // 654
    196,    // 655
    576,    // 656
    736,    // 657
    219,    // 658
    564,    // 659
    6,      // 660
    667,    // 661
    753,    // 662
    396,    // 663
    663,    // 664
    432,    // 665
    330,    // 666
    146,    // 667
    268,    // 668
    72,     // 669
    25,     // 670
    192,    // 671
    332,    // 672
    749,    // 673
    253,    // 674
    209,    // 675
    99,     // 676
    836,    // 677
    295,    // 678
    144,    // 679
    172,    // 680
    741,    // 681
    501,    // 682
    290,    // 683
    582,    // 684
    583,    // 685
    346,    // 686
    523,    // 687
    326,    // 688
    35,     // 689
    743,    // 690
    744,    // 691
    292,    // 692
    44,     // 693
    160,    // 694
    386,    // 695
    159,    // 696
    327,    // 697
    493,    // 698
    185,    // 699
    186,    // 700
    293,    // 701
    509,    // 702
    784,    // 703
    303,    // 704
    125,    // 705
    304,    // 706
    301,    // 707
    839,    // 708
    164,    // 709
    347,    // 710
    165,    // 711
    494,    // 712
    384,    // 713
    96,     // 714
    7,      // 715
    786,    // 716
    195,    // 717
    439,    // 718
    169,    // 719
    171,    // 720
    433,    // 721
    742,    // 722
    533,    // 723

    // Start of custom entries
    ProfileID::ActorSpawner,                // 724
    ProfileID::ParaBones,                   // 725
    ProfileID::CustomDoor,                  // 726
    ProfileID::FakeActor,                   // 727
    ProfileID::PAcorn,                      // 728
    ProfileID::StarCoinShard,               // 729
    ProfileID::BeepBlock,                   // 730
    ProfileID::FallingChestnut,             // 731
    ProfileID::TaskChanger,                 // 732
    ProfileID::Cataquack,                   // 733
    ProfileID::TimeClock,                   // 734
    ProfileID::RedBlueBlock,                // 735
    ProfileID::JumboRay,                    // 736
    ProfileID::EffectSpawner,               // 737
    ProfileID::RainbowLight,                // 738
    ProfileID::SoundPlayer,                 // 739
    ProfileID::DebugActor,                  // 740
    ProfileID::LiquidOverlay,               // 741
    ProfileID::Stingby,                     // 742
    ProfileID::Kamiya,                      // 743
    ProfileID::ModelLoader,                 // 744
    ProfileID::StringBank,                  // 745
    ProfileID::SwitchBlockEventActivator,   // 746
    ProfileID::UniversalBossController,     // 747
    ProfileID::GiantSkewer,                 // 748
    ProfileID::Scuttlebug,                  // 749
    ProfileID::AngryGrrrol,                 // 750
    ProfileID::PoisonMushroom,              // 751
    ProfileID::MagicPlatform,               // 752
    ProfileID::ColdFuzzy,                   // 753
    ProfileID::WavyWater,                   // 754
    ProfileID::WavyPoison,                  // 755
    ProfileID::WavyQuicksand,               // 756
    ProfileID::LayerChanger,                // 757
    ProfileID::Biddybud,                    // 758
    ProfileID::HelicalBar,                  // 759
    ProfileID::BasaltBones,                 // 760
    ProfileID::Flaptor,                     // 761
    ProfileID::StarCoinShardMgr,            // 762
    ProfileID::SwitchBlock,                 // 763
    ProfileID::PowerupSwitcher,             // 764
    ProfileID::Minecart,                    // 765
    ProfileID::TripleBlock,                 // 766
    ProfileID::PhysicsModifier,             // 767
    ProfileID::MusicNote,                   // 768
    ProfileID::MusicNoteMgr,                // 769
    ProfileID::Peepa,                       // 770
    ProfileID::Solid,                       // 771
    ProfileID::UniversalMovementController, // 772
    ProfileID::TimeChanger,                 // 773
    ProfileID::HammerBlock,                 // 774
    ProfileID::NullActor,                   // 775
    ProfileID::NullActor,                   // 776
    ProfileID::NullActor,                   // 777
    ProfileID::NullActor,                   // 778
    ProfileID::NullActor,                   // 779
    ProfileID::NullActor,                   // 780
    ProfileID::NullActor,                   // 781
    ProfileID::NullActor,                   // 782
    ProfileID::NullActor,                   // 783
    ProfileID::NullActor,                   // 784
    ProfileID::NullActor,                   // 785
    ProfileID::NullActor,                   // 786
    ProfileID::NullActor,                   // 787
    ProfileID::NullActor,                   // 788
    ProfileID::NullActor,                   // 789
    ProfileID::NullActor,                   // 790
    ProfileID::NullActor,                   // 791
    ProfileID::NullActor,                   // 792
    ProfileID::NullActor,                   // 793
    ProfileID::NullActor,                   // 794
    ProfileID::NullActor,                   // 795
    ProfileID::NullActor,                   // 796
    ProfileID::NullActor,                   // 797
    ProfileID::NullActor,                   // 798
    ProfileID::NullActor,                   // 799
//! Reserved Area 1
    ProfileID::NullActor,                   // 800
    ProfileID::NullActor,                   // 801
    ProfileID::NullActor,                   // 802
    ProfileID::NullActor,                   // 803
    ProfileID::NullActor,                   // 804
    ProfileID::NullActor,                   // 805
    ProfileID::NullActor,                   // 806
    ProfileID::NullActor,                   // 807
    ProfileID::NullActor,                   // 808
    ProfileID::NullActor,                   // 809
    ProfileID::NullActor,                   // 810
    ProfileID::NullActor,                   // 811
    ProfileID::NullActor,                   // 812
    ProfileID::NullActor,                   // 813
    ProfileID::NullActor,                   // 814
    ProfileID::NullActor,                   // 815
    ProfileID::NullActor,                   // 816
    ProfileID::NullActor,                   // 817
    ProfileID::NullActor,                   // 818
    ProfileID::NullActor,                   // 819
    ProfileID::NullActor,                   // 820
    ProfileID::NullActor,                   // 821
    ProfileID::NullActor,                   // 822
    ProfileID::NullActor,                   // 823
    ProfileID::NullActor,                   // 824
    ProfileID::NullActor,                   // 825
    ProfileID::NullActor,                   // 826
    ProfileID::NullActor,                   // 827
    ProfileID::NullActor,                   // 828
    ProfileID::NullActor,                   // 829
    ProfileID::NullActor,                   // 830
    ProfileID::NullActor,                   // 831
    ProfileID::NullActor,                   // 832
    ProfileID::NullActor,                   // 833
    ProfileID::NullActor,                   // 834
    ProfileID::NullActor,                   // 835
    ProfileID::NullActor,                   // 836
    ProfileID::NullActor,                   // 837
    ProfileID::NullActor,                   // 838
    ProfileID::NullActor,                   // 839
    ProfileID::NullActor,                   // 840
    ProfileID::NullActor,                   // 841
    ProfileID::NullActor,                   // 842
    ProfileID::NullActor,                   // 843
    ProfileID::NullActor,                   // 844
    ProfileID::NullActor,                   // 845
    ProfileID::NullActor,                   // 846
    ProfileID::NullActor,                   // 847
    ProfileID::NullActor,                   // 848
    ProfileID::NullActor,                   // 849
//! Reserved Area 2
    ProfileID::NullActor,                   // 850
    ProfileID::NullActor,                   // 851
    ProfileID::NullActor,                   // 852
    ProfileID::NullActor,                   // 853
    ProfileID::NullActor,                   // 854
    ProfileID::NullActor,                   // 855
    ProfileID::NullActor,                   // 856
    ProfileID::NullActor,                   // 857
    ProfileID::NullActor,                   // 858
    ProfileID::NullActor,                   // 859
    ProfileID::NullActor,                   // 860
    ProfileID::NullActor,                   // 861
    ProfileID::NullActor,                   // 862
    ProfileID::NullActor,                   // 863
    ProfileID::NullActor,                   // 864
    ProfileID::NullActor,                   // 865
    ProfileID::NullActor,                   // 866
    ProfileID::NullActor,                   // 867
    ProfileID::NullActor,                   // 868
    ProfileID::NullActor,                   // 869
    ProfileID::NullActor,                   // 870
    ProfileID::NullActor,                   // 871
    ProfileID::NullActor,                   // 872
    ProfileID::NullActor,                   // 873
    ProfileID::NullActor,                   // 874
    ProfileID::NullActor,                   // 875
    ProfileID::NullActor,                   // 876
    ProfileID::NullActor,                   // 877
    ProfileID::NullActor,                   // 878
    ProfileID::NullActor,                   // 879
    ProfileID::NullActor,                   // 880
    ProfileID::NullActor,                   // 881
    ProfileID::NullActor,                   // 882
    ProfileID::NullActor,                   // 883
    ProfileID::NullActor,                   // 884
    ProfileID::NullActor,                   // 885
    ProfileID::NullActor,                   // 886
    ProfileID::NullActor,                   // 887
    ProfileID::NullActor,                   // 888
    ProfileID::NullActor,                   // 889
    ProfileID::NullActor,                   // 890
    ProfileID::NullActor,                   // 891
    ProfileID::NullActor,                   // 892
    ProfileID::NullActor,                   // 893
    ProfileID::NullActor,                   // 894
    ProfileID::NullActor,                   // 895
    ProfileID::NullActor,                   // 896
    ProfileID::NullActor,                   // 897
    ProfileID::NullActor,                   // 898
    ProfileID::NullActor,                   // 899
    ProfileID::NullActor,                   // 900
//! Continue below here
    ProfileID::Splounder,                   // 772
};
