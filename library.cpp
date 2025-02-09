#include "library.h"

#include "sentencepiece_processor.h"
#include <vector>
#include <cstring>
#include <iostream>

#include "sentencepiece_trainer.h"

void* spp_create() {
    return new sentencepiece::SentencePieceProcessor();
}

int spp_load(void* processor, const char* model_file) {
    const auto sp = static_cast<sentencepiece::SentencePieceProcessor*>(processor);
    if (const auto status = sp->Load(model_file); status.ok()) {
        return 0;
    }
    return 1;
}

int spp_encode(void* processor, const char* input, int** output) {
    const auto sp = static_cast<sentencepiece::SentencePieceProcessor*>(processor);
    std::vector<int> ids;

    if (const auto status = sp->Encode(input, &ids); !status.ok()) {
        return -1;
    }
    const int length = ids.size();
    *output = new int[length];
    std::memcpy(*output, ids.data(), length * sizeof(int));
    return length;
}

void spp_free_array(const int* arr) {
    delete[] arr;
}

void spp_destroy(void* processor) {
    const auto* sp = static_cast<sentencepiece::SentencePieceProcessor*>(processor);
    delete sp;
}

int spp_get_piece_size(void* processor) {
    const auto sp = static_cast<sentencepiece::SentencePieceProcessor*>(processor);
    return sp->GetPieceSize();
}

int spp_piece_to_id(void* processor, const char *piece) {
    const auto sp = static_cast<sentencepiece::SentencePieceProcessor*>(processor);
    return sp->PieceToId(piece);
}

const char* spp_id_to_piece(void *processor, int piece_id) {
    static std::string last_piece;
    const auto sp = static_cast<sentencepiece::SentencePieceProcessor*>(processor);
    last_piece = sp->IdToPiece(piece_id);
    return last_piece.c_str();
}

bool spp_is_unknown(void *processor, const int piece) {
    const auto sp = static_cast<sentencepiece::SentencePieceProcessor*>(processor);
    return sp->IsUnknown(piece);
}

bool spp_is_control(void *processor, const int piece) {
    const auto sp = static_cast<sentencepiece::SentencePieceProcessor*>(processor);
    return sp->IsControl(piece);
}

int spp_bos_id(void *processor) {
    const auto sp = static_cast<sentencepiece::SentencePieceProcessor*>(processor);
    return sp->bos_id();
}

int spp_eos_id(void *processor) {
    const auto sp = static_cast<sentencepiece::SentencePieceProcessor*>(processor);
    return sp->eos_id();
}

int spp_pad_id(void *processor) {
    const auto sp = static_cast<sentencepiece::SentencePieceProcessor*>(processor);
    return sp->pad_id();
}

int spp_unk_id(void *processor) {
    const auto sp = static_cast<sentencepiece::SentencePieceProcessor*>(processor);
    return sp->unk_id();
}

void spp_set_encode_extra_options(void* processor, const char *piece) {
    const auto sp = static_cast<sentencepiece::SentencePieceProcessor*>(processor);
    sp->SetEncodeExtraOptions(piece);
}