#pragma once

#include "common.h"

#include <chrono>
#include <vector>
#include <cassert>

class Actor;
class Aura;

class Action {
	public:
		Action(const char* identifier) : _identifier(identifier), _identifierHash(identifier) {}
		virtual ~Action();

		bool isReady(const Actor* source) const;
		bool isUsable(const Actor* source) const;
		bool resolve(Actor* source, Actor* target) const;

		FNV1AHash identifierHash() const { return _identifierHash; }
		virtual const std::string& identifier() const { return _identifier; }

		virtual std::chrono::microseconds castTime(const Actor* source) const { return castTime(); }
		virtual std::chrono::microseconds cooldown() const { return 0_us; }
		virtual std::chrono::microseconds animationLock() const { return 1_s; }
		virtual bool isOffGlobalCooldown() const { return false; }

		virtual int damage(const Actor* source, const Actor* target) const { return damage(); }

		virtual double criticalHitChance(const Actor* source, double base) const { return base; }

		virtual const std::vector<Aura*>& sourceAuras() const { return _sourceAuras; }
		virtual const std::vector<Aura*>& targetAuras() const { return _targetAuras; }

		virtual int tpCost() const { return 0; }
		virtual int tpRestoration() const { return 0; }

		virtual int mpCost(const Actor* source) const { return mpCost(); }
		virtual int mpRestoration(const Actor* source) const { return 0; }
			
		virtual const Action* replacement(const Actor* source, const Actor* target) const { return nullptr; }

	protected:
		const std::string _identifier;
		const FNV1AHash _identifierHash;
	
		std::vector<Aura*> _sourceAuras;
		std::vector<Aura*> _targetAuras;

		virtual int damage() const { return 0; }
		virtual int mpCost() const { return 0; }
		virtual std::chrono::microseconds castTime() const { return 0_us; }
		virtual void resolution(Actor* source, Actor* target, bool isCritical) const {}
		virtual bool requirements(const Actor* source) const { return true; }
};