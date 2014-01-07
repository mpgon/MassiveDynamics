using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Net;
using System.Web;
using System.Web.Mvc;
using SocialGameWebSite.Models;
using MassiveDynamicsWebSite.Models;

namespace SocialGameWebSite.Controllers
{
    public class RelacaoController : Controller
    {
        private ApplicationDbContext db = new ApplicationDbContext();

        // GET: /Relacao/
        public ActionResult Index()
        {
            var relacao = db.Relacao.Include(r => r.estadorelacao);
            return View(relacao.ToList());
        }

        // GET: /Relacao/Details/5
        public ActionResult Details(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Relacao relacao = db.Relacao.Find(id);
            if (relacao == null)
            {
                return HttpNotFound();
            }
            return View(relacao);
        }

        // GET: /Relacao/Create
        public ActionResult Create()
        {
            ViewBag.estadorelacaoID = new SelectList(db.EstadoRelacao, "ID", "estado");
            return View();
        }

        // POST: /Relacao/Create
		// To protect from over posting attacks, please enable the specific properties you want to bind to, for 
		// more details see http://go.microsoft.com/fwlink/?LinkId=317598.
		// 
		// Example: public ActionResult Update([Bind(Include="ExampleProperty1,ExampleProperty2")] Model model)
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Create(Relacao relacao)
        {
            if (ModelState.IsValid)
            {
                db.Relacao.Add(relacao);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            ViewBag.estadorelacaoID = new SelectList(db.EstadoRelacao, "ID", "estado", relacao.estadorelacaoID);
            return View(relacao);
        }

        // GET: /Relacao/Edit/5
        public ActionResult Edit(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Relacao relacao = db.Relacao.Find(id);
            if (relacao == null)
            {
                return HttpNotFound();
            }
            ViewBag.estadorelacaoID = new SelectList(db.EstadoRelacao, "ID", "estado", relacao.estadorelacaoID);
            return View(relacao);
        }

        // POST: /Relacao/Edit/5
		// To protect from over posting attacks, please enable the specific properties you want to bind to, for 
		// more details see http://go.microsoft.com/fwlink/?LinkId=317598.
		// 
		// Example: public ActionResult Update([Bind(Include="ExampleProperty1,ExampleProperty2")] Model model)
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Edit(Relacao relacao)
        {
            if (ModelState.IsValid)
            {
                db.Entry(relacao).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            ViewBag.estadorelacaoID = new SelectList(db.EstadoRelacao, "ID", "estado", relacao.estadorelacaoID);
            return View(relacao);
        }

        // GET: /Relacao/Delete/5
        public ActionResult Delete(int? id)
        {
            if (id == null)
            {
				return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Relacao relacao = db.Relacao.Find(id);
            if (relacao == null)
            {
                return HttpNotFound();
            }
            return View(relacao);
        }

        // POST: /Relacao/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public ActionResult DeleteConfirmed(int id)
        {
            Relacao relacao = db.Relacao.Find(id);
            db.Relacao.Remove(relacao);
            db.SaveChanges();
            return RedirectToAction("Index");
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}
