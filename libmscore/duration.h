//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2008-2011 Werner Schweer
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2
//  as published by the Free Software Foundation and appearing in
//  the file LICENCE.GPL
//=============================================================================

#ifndef __DURATION_H__
#define __DURATION_H__

#include "config.h"
#include "element.h"
#include "cursor.h"
#include "durationtype.h"

namespace Ms {

class Tuplet;
class Beam;
class Spanner;

//---------------------------------------------------------
//   @@ DurationElementW
//   @W DurationElement
///   Virtual base class for Chord, Rest and Tuplet.
//
//   @P duration       Fraction  duration (as written)
//   @P globalDuration Fraction  played duration
//   @S track,generated,color,visible,selected,user_off,placement,autoplace,z,system_flag,duration
//---------------------------------------------------------

#ifdef SCRIPT_INTERFACE
class DurationElementW : public ElementW {
      Q_OBJECT
      Q_PROPERTY(FractionWrapper* duration READ durationW WRITE setDurationW)
      Q_PROPERTY(FractionWrapper* globalDuration READ globalDurW)
   public:
      DurationElementW() : ElementW() {}
      DurationElementW(ScoreElement* _e) : ElementW(_e) {}
      DurationElement* durationElement();
      FractionWrapper* durationW();
      void setDurationW(FractionWrapper* f);
      FractionWrapper* globalDurW();
      };
//@E
#endif

class DurationElement : public Element {
      friend class DurationElementW;
      Fraction _duration;
      Tuplet* _tuplet;

#ifdef SCRIPT_INTERFACE
      Q_GADGET
      Q_PROPERTY(FractionWrapper* duration READ durationW WRITE setDurationW)
      Q_PROPERTY(FractionWrapper* globalDuration READ globalDurW)

      void setDurationW(FractionWrapper* f)  { _duration = f->fraction(); }
      FractionWrapper* durationW() const     { return new FractionWrapper(_duration); }
      FractionWrapper* globalDurW() const    { return new FractionWrapper(globalDuration()); }
#endif

   public:
      DurationElement(Score* s);
      DurationElement(const DurationElement& e);
      ~DurationElement();

      virtual Measure* measure() const    { return (Measure*)(parent()); }

      virtual bool readProperties(XmlReader& e);
      virtual void writeProperties(XmlWriter& xml) const;
      void writeTuplet(XmlWriter& xml);

      void setTuplet(Tuplet* t)           { _tuplet = t;      }
      Tuplet* tuplet() const              { return _tuplet;   }
      Tuplet* topTuplet() const;
      virtual Beam* beam() const          { return 0;         }
      int actualTicks() const;
      Fraction actualFraction() const;

      virtual Fraction duration() const   { return _duration; }
      Fraction globalDuration() const;
      void setDuration(const Fraction& f) { _duration = f;    }

      virtual QVariant getProperty(P_ID propertyId) const override;
      virtual bool setProperty(P_ID propertyId, const QVariant&) override;
      virtual void supportedProperties(QList<P_ID>& dest, bool writeable = false) override;
      };


}     // namespace Ms
#endif

