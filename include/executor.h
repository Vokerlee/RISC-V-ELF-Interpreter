#ifndef EXECUTOR_H_
#define EXECUTOR_H_

#include "config.h"
#include "utils.hpp"
#include "hart.h"

namespace risc
{
    class Hart;
    class Instruction;

    class Executor
    {
        static enum DebugRegime dbg_regime_;

    public:

        virtual bool operator()(Hart* hart, const Instruction& instr) = 0;
    };

    class ExecutorRV32I_LUI : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_AUIPC : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_JAL : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_JALR : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_BEQ : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_BNE : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_BLT : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_BGE : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_BLTU : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_BGEU : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_LB : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_LH : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_LW : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_LBU : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_LHU : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_SB : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_SH : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_SW : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_ADDI : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_SLTI : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_SLTIU: public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_XORI : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_ORI : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_ANDI : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_SLLI : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_SRLI : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_SRAI : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_ADD : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_SUB : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_SLL : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_SLT : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_SLTU : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_XOR : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_SRL : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_SRA : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_OR : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_AND : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_FENCE : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_ECALL : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };

    class ExecutorRV32I_EBREAK : public Executor
    {
    public:
        virtual bool operator()(Hart* hart, const Instruction& instr) final;
    };
}

#endif // !EXECUTOR_H_
