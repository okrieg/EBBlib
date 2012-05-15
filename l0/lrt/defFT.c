/*
 * Copyright (C) 2011 by Project SESA, Boston University
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <config.h>
#include <stdint.h>
#include <l0/lrt/trans.h>
#include <l0/lrt/trans-def.h>
#include <l0/lrt/defFT.h>

//takes the function table pointer and function number and
//invokes the miss handler then
//returns the function pointer to be called
void *GenericDefaultFunc(EBBRep **_self, FuncNum fnum) {
  //the default ftable is the second word in the trans, subtract 1
  //word to get the LTrans
  EBBLTrans *self = (EBBLTrans *)(*_self-1);
  EBBGTrans *gt = (EBBGTrans *)lrt_trans_lt2gt((struct lrt_trans *)self);
  EBBRC ret = gt->mf(_self, self, fnum, gt->arg);
  if(EBBRC_SUCCESS(ret)) {
    //return the function we wanted to call originally
    return (**_self)[fnum];
  }
  return (void *)ret; //return the error code
}

EBBFunc EBBDefFT[EBB_TRANS_MAX_FUNCS] = {
  (EBBFunc)EBBDefFunc_0,
  (EBBFunc)EBBDefFunc_1,
  (EBBFunc)EBBDefFunc_2,
  (EBBFunc)EBBDefFunc_3,
  (EBBFunc)EBBDefFunc_4,
  (EBBFunc)EBBDefFunc_5,
  (EBBFunc)EBBDefFunc_6,
  (EBBFunc)EBBDefFunc_7,
  (EBBFunc)EBBDefFunc_8,
  (EBBFunc)EBBDefFunc_9,
  (EBBFunc)EBBDefFunc_10,
  (EBBFunc)EBBDefFunc_11,
  (EBBFunc)EBBDefFunc_12,
  (EBBFunc)EBBDefFunc_13,
  (EBBFunc)EBBDefFunc_14,
  (EBBFunc)EBBDefFunc_15,
  (EBBFunc)EBBDefFunc_16,
  (EBBFunc)EBBDefFunc_17,
  (EBBFunc)EBBDefFunc_18,
  (EBBFunc)EBBDefFunc_19,
  (EBBFunc)EBBDefFunc_20,
  (EBBFunc)EBBDefFunc_21,
  (EBBFunc)EBBDefFunc_22,
  (EBBFunc)EBBDefFunc_23,
  (EBBFunc)EBBDefFunc_24,
  (EBBFunc)EBBDefFunc_25,
  (EBBFunc)EBBDefFunc_26,
  (EBBFunc)EBBDefFunc_27,
  (EBBFunc)EBBDefFunc_28,
  (EBBFunc)EBBDefFunc_29,
  (EBBFunc)EBBDefFunc_30,
  (EBBFunc)EBBDefFunc_31,
  (EBBFunc)EBBDefFunc_32,
  (EBBFunc)EBBDefFunc_33,
  (EBBFunc)EBBDefFunc_34,
  (EBBFunc)EBBDefFunc_35,
  (EBBFunc)EBBDefFunc_36,
  (EBBFunc)EBBDefFunc_37,
  (EBBFunc)EBBDefFunc_38,
  (EBBFunc)EBBDefFunc_39,
  (EBBFunc)EBBDefFunc_40,
  (EBBFunc)EBBDefFunc_41,
  (EBBFunc)EBBDefFunc_42,
  (EBBFunc)EBBDefFunc_43,
  (EBBFunc)EBBDefFunc_44,
  (EBBFunc)EBBDefFunc_45,
  (EBBFunc)EBBDefFunc_46,
  (EBBFunc)EBBDefFunc_47,
  (EBBFunc)EBBDefFunc_48,
  (EBBFunc)EBBDefFunc_49,
  (EBBFunc)EBBDefFunc_50,
  (EBBFunc)EBBDefFunc_51,
  (EBBFunc)EBBDefFunc_52,
  (EBBFunc)EBBDefFunc_53,
  (EBBFunc)EBBDefFunc_54,
  (EBBFunc)EBBDefFunc_55,
  (EBBFunc)EBBDefFunc_56,
  (EBBFunc)EBBDefFunc_57,
  (EBBFunc)EBBDefFunc_58,
  (EBBFunc)EBBDefFunc_59,
  (EBBFunc)EBBDefFunc_60,
  (EBBFunc)EBBDefFunc_61,
  (EBBFunc)EBBDefFunc_62,
  (EBBFunc)EBBDefFunc_63,
  (EBBFunc)EBBDefFunc_64,
  (EBBFunc)EBBDefFunc_65,
  (EBBFunc)EBBDefFunc_66,
  (EBBFunc)EBBDefFunc_67,
  (EBBFunc)EBBDefFunc_68,
  (EBBFunc)EBBDefFunc_69,
  (EBBFunc)EBBDefFunc_70,
  (EBBFunc)EBBDefFunc_71,
  (EBBFunc)EBBDefFunc_72,
  (EBBFunc)EBBDefFunc_73,
  (EBBFunc)EBBDefFunc_74,
  (EBBFunc)EBBDefFunc_75,
  (EBBFunc)EBBDefFunc_76,
  (EBBFunc)EBBDefFunc_77,
  (EBBFunc)EBBDefFunc_78,
  (EBBFunc)EBBDefFunc_79,
  (EBBFunc)EBBDefFunc_80,
  (EBBFunc)EBBDefFunc_81,
  (EBBFunc)EBBDefFunc_82,
  (EBBFunc)EBBDefFunc_83,
  (EBBFunc)EBBDefFunc_84,
  (EBBFunc)EBBDefFunc_85,
  (EBBFunc)EBBDefFunc_86,
  (EBBFunc)EBBDefFunc_87,
  (EBBFunc)EBBDefFunc_88,
  (EBBFunc)EBBDefFunc_89,
  (EBBFunc)EBBDefFunc_90,
  (EBBFunc)EBBDefFunc_91,
  (EBBFunc)EBBDefFunc_92,
  (EBBFunc)EBBDefFunc_93,
  (EBBFunc)EBBDefFunc_94,
  (EBBFunc)EBBDefFunc_95,
  (EBBFunc)EBBDefFunc_96,
  (EBBFunc)EBBDefFunc_97,
  (EBBFunc)EBBDefFunc_98,
  (EBBFunc)EBBDefFunc_99,
  (EBBFunc)EBBDefFunc_100,
  (EBBFunc)EBBDefFunc_101,
  (EBBFunc)EBBDefFunc_102,
  (EBBFunc)EBBDefFunc_103,
  (EBBFunc)EBBDefFunc_104,
  (EBBFunc)EBBDefFunc_105,
  (EBBFunc)EBBDefFunc_106,
  (EBBFunc)EBBDefFunc_107,
  (EBBFunc)EBBDefFunc_108,
  (EBBFunc)EBBDefFunc_109,
  (EBBFunc)EBBDefFunc_110,
  (EBBFunc)EBBDefFunc_111,
  (EBBFunc)EBBDefFunc_112,
  (EBBFunc)EBBDefFunc_113,
  (EBBFunc)EBBDefFunc_114,
  (EBBFunc)EBBDefFunc_115,
  (EBBFunc)EBBDefFunc_116,
  (EBBFunc)EBBDefFunc_117,
  (EBBFunc)EBBDefFunc_118,
  (EBBFunc)EBBDefFunc_119,
  (EBBFunc)EBBDefFunc_120,
  (EBBFunc)EBBDefFunc_121,
  (EBBFunc)EBBDefFunc_122,
  (EBBFunc)EBBDefFunc_123,
  (EBBFunc)EBBDefFunc_124,
  (EBBFunc)EBBDefFunc_125,
  (EBBFunc)EBBDefFunc_126,
  (EBBFunc)EBBDefFunc_127,
  (EBBFunc)EBBDefFunc_128,
  (EBBFunc)EBBDefFunc_129,
  (EBBFunc)EBBDefFunc_130,
  (EBBFunc)EBBDefFunc_131,
  (EBBFunc)EBBDefFunc_132,
  (EBBFunc)EBBDefFunc_133,
  (EBBFunc)EBBDefFunc_134,
  (EBBFunc)EBBDefFunc_135,
  (EBBFunc)EBBDefFunc_136,
  (EBBFunc)EBBDefFunc_137,
  (EBBFunc)EBBDefFunc_138,
  (EBBFunc)EBBDefFunc_139,
  (EBBFunc)EBBDefFunc_140,
  (EBBFunc)EBBDefFunc_141,
  (EBBFunc)EBBDefFunc_142,
  (EBBFunc)EBBDefFunc_143,
  (EBBFunc)EBBDefFunc_144,
  (EBBFunc)EBBDefFunc_145,
  (EBBFunc)EBBDefFunc_146,
  (EBBFunc)EBBDefFunc_147,
  (EBBFunc)EBBDefFunc_148,
  (EBBFunc)EBBDefFunc_149,
  (EBBFunc)EBBDefFunc_150,
  (EBBFunc)EBBDefFunc_151,
  (EBBFunc)EBBDefFunc_152,
  (EBBFunc)EBBDefFunc_153,
  (EBBFunc)EBBDefFunc_154,
  (EBBFunc)EBBDefFunc_155,
  (EBBFunc)EBBDefFunc_156,
  (EBBFunc)EBBDefFunc_157,
  (EBBFunc)EBBDefFunc_158,
  (EBBFunc)EBBDefFunc_159,
  (EBBFunc)EBBDefFunc_160,
  (EBBFunc)EBBDefFunc_161,
  (EBBFunc)EBBDefFunc_162,
  (EBBFunc)EBBDefFunc_163,
  (EBBFunc)EBBDefFunc_164,
  (EBBFunc)EBBDefFunc_165,
  (EBBFunc)EBBDefFunc_166,
  (EBBFunc)EBBDefFunc_167,
  (EBBFunc)EBBDefFunc_168,
  (EBBFunc)EBBDefFunc_169,
  (EBBFunc)EBBDefFunc_170,
  (EBBFunc)EBBDefFunc_171,
  (EBBFunc)EBBDefFunc_172,
  (EBBFunc)EBBDefFunc_173,
  (EBBFunc)EBBDefFunc_174,
  (EBBFunc)EBBDefFunc_175,
  (EBBFunc)EBBDefFunc_176,
  (EBBFunc)EBBDefFunc_177,
  (EBBFunc)EBBDefFunc_178,
  (EBBFunc)EBBDefFunc_179,
  (EBBFunc)EBBDefFunc_180,
  (EBBFunc)EBBDefFunc_181,
  (EBBFunc)EBBDefFunc_182,
  (EBBFunc)EBBDefFunc_183,
  (EBBFunc)EBBDefFunc_184,
  (EBBFunc)EBBDefFunc_185,
  (EBBFunc)EBBDefFunc_186,
  (EBBFunc)EBBDefFunc_187,
  (EBBFunc)EBBDefFunc_188,
  (EBBFunc)EBBDefFunc_189,
  (EBBFunc)EBBDefFunc_190,
  (EBBFunc)EBBDefFunc_191,
  (EBBFunc)EBBDefFunc_192,
  (EBBFunc)EBBDefFunc_193,
  (EBBFunc)EBBDefFunc_194,
  (EBBFunc)EBBDefFunc_195,
  (EBBFunc)EBBDefFunc_196,
  (EBBFunc)EBBDefFunc_197,
  (EBBFunc)EBBDefFunc_198,
  (EBBFunc)EBBDefFunc_199,
  (EBBFunc)EBBDefFunc_200,
  (EBBFunc)EBBDefFunc_201,
  (EBBFunc)EBBDefFunc_202,
  (EBBFunc)EBBDefFunc_203,
  (EBBFunc)EBBDefFunc_204,
  (EBBFunc)EBBDefFunc_205,
  (EBBFunc)EBBDefFunc_206,
  (EBBFunc)EBBDefFunc_207,
  (EBBFunc)EBBDefFunc_208,
  (EBBFunc)EBBDefFunc_209,
  (EBBFunc)EBBDefFunc_210,
  (EBBFunc)EBBDefFunc_211,
  (EBBFunc)EBBDefFunc_212,
  (EBBFunc)EBBDefFunc_213,
  (EBBFunc)EBBDefFunc_214,
  (EBBFunc)EBBDefFunc_215,
  (EBBFunc)EBBDefFunc_216,
  (EBBFunc)EBBDefFunc_217,
  (EBBFunc)EBBDefFunc_218,
  (EBBFunc)EBBDefFunc_219,
  (EBBFunc)EBBDefFunc_220,
  (EBBFunc)EBBDefFunc_221,
  (EBBFunc)EBBDefFunc_222,
  (EBBFunc)EBBDefFunc_223,
  (EBBFunc)EBBDefFunc_224,
  (EBBFunc)EBBDefFunc_225,
  (EBBFunc)EBBDefFunc_226,
  (EBBFunc)EBBDefFunc_227,
  (EBBFunc)EBBDefFunc_228,
  (EBBFunc)EBBDefFunc_229,
  (EBBFunc)EBBDefFunc_230,
  (EBBFunc)EBBDefFunc_231,
  (EBBFunc)EBBDefFunc_232,
  (EBBFunc)EBBDefFunc_233,
  (EBBFunc)EBBDefFunc_234,
  (EBBFunc)EBBDefFunc_235,
  (EBBFunc)EBBDefFunc_236,
  (EBBFunc)EBBDefFunc_237,
  (EBBFunc)EBBDefFunc_238,
  (EBBFunc)EBBDefFunc_239,
  (EBBFunc)EBBDefFunc_240,
  (EBBFunc)EBBDefFunc_241,
  (EBBFunc)EBBDefFunc_242,
  (EBBFunc)EBBDefFunc_243,
  (EBBFunc)EBBDefFunc_244,
  (EBBFunc)EBBDefFunc_245,
  (EBBFunc)EBBDefFunc_246,
  (EBBFunc)EBBDefFunc_247,
  (EBBFunc)EBBDefFunc_248,
  (EBBFunc)EBBDefFunc_249,
  (EBBFunc)EBBDefFunc_250,
  (EBBFunc)EBBDefFunc_251,
  (EBBFunc)EBBDefFunc_252,
  (EBBFunc)EBBDefFunc_253,
  (EBBFunc)EBBDefFunc_254,
  (EBBFunc)EBBDefFunc_255
};